//
// Created by omer on 5/13/2025.
//

#include "EvaluateAllMoves.h"


// Constructor: initialize with board and depth
EvaluateAllMoves::EvaluateAllMoves(int depth, const Board& board) : depth(depth), board(board){
    tempBoard = new Board(board); // Defensive copy
}

// Destructor: clean up
EvaluateAllMoves::~EvaluateAllMoves() {
    delete tempBoard;
}

// Evaluate all legal moves, scoring them in parallel using a thread pool
MyPriorityQueue<std::unique_ptr<Move>> EvaluateAllMoves::evaluateAllMoves(int numThreads) {
    vector<std::unique_ptr<Move>> allValidMoves = getAllValidMoves();
    ThreadsPool pool(numThreads);
    ThreadSafePriorityQueue<std::unique_ptr<Move>> resultQueue;
    std::vector<std::future<void>> futures;
    std::atomic<bool> stopFlag{false}; // Used for early exit if high score found

    // Launch a job for each move
    for (auto& move : allValidMoves) {
        Move moveCopy = *move;
        auto job = [this, moveCopy, &resultQueue, &stopFlag]() mutable {
            if (stopFlag.load()) return;
            Board privateBoard = this->board;
            EvaluateAllMoves evaluator(this->depth, privateBoard);
            int score = evaluator.evaluateOneMove(&moveCopy, this->depth);
            moveCopy.setScore(score);
            // Early exit if a "winning" move is found
            if (score >= Constants::HIGH_SCORE_THRESHOLD) {
                stopFlag.store(true);
            }
            if (score >= 0) {
                resultQueue.push(std::make_unique<Move>(moveCopy));
            }
        };
        futures.push_back(pool.enqueue(job));
    }

    // Wait for all threads
    for (auto& f : futures) {
        f.get();
    }

    // Collect results into a priority queue (not thread-safe)
    MyPriorityQueue<std::unique_ptr<Move>> topMoves;
    while (!resultQueue.empty()) {
        try {
            topMoves.push(resultQueue.pull());
        } catch (...) {
            break;
        }
    }
    return topMoves;
}

// Generate all legal moves for the current player
vector<std::unique_ptr<Move>> EvaluateAllMoves::getAllValidMoves() {
    vector<std::unique_ptr<Move>> allValidMoves;
    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* pieceSource = (*tempBoard)[i][j];
            if(pieceSource != nullptr && pieceSource->getColor() == tempBoard->getTurn()) {
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        int moveStatus = tempBoard->isValidMove(i, j, r, c);
                        if(moveStatus > Constants::CHECK_STATUS){
                            // Only valid moves are included
                            allValidMoves.emplace_back(std::make_unique<Move>(i, j, r, c, moveStatus)); // Add the move to the list
                        }
                    }
                }
            }
        }
    }
    return allValidMoves;
}

// Evaluate net threats created by a move (threats to enemy, dangers from enemy)
int EvaluateAllMoves::moveMakeOrInThreats(Move* move, Piece* movedPiece) {
    auto [endRow, endCol] = move->getEndPosition();
    if(!movedPiece) return 0;
    int threats = 0;
    int dangers = 0;

    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Piece* enemyPiece = (*tempBoard)[i][j];
            if(enemyPiece && enemyPiece->getColor() != movedPiece->getColor()) {
                // Check if after the move, the piece threatens an enemy piece
                if(tempBoard->isValidMove(endRow, endCol, i, j) > Constants::CHECK_STATUS) {
                        threats += enemyPiece->getValue();
                }
                // Temporarily switch turn: can enemy threaten us?
                tempBoard->changeTurn();
                if(tempBoard->isValidMove(i, j, endRow, endCol) > Constants::CHECK_STATUS) {
                        dangers += movedPiece->getValue();
                }
                tempBoard->changeTurn();
            }
        }
    }
    return threats - dangers;
}

// Compute score for a move based on material, position, development, and threats
int EvaluateAllMoves::getMoveScore(Move *move, Piece *target, Piece *source) {
    auto [endRow, endCol] = move->getEndPosition();
    auto [startRow, startCol] = move->getStartPosition();
    int score = 0;

    if(move->getMoveStatus() == 41){
        score += 10; // Bonus: gives check
    }
    if(target){
        int captureValue = target->getValue();
        // Bonus if small piece captures big piece
        if(source->getValue() < target->getValue()) {
            score += captureValue + (captureValue - source->getValue()) / 2;
        } else {
            score += captureValue;
        }
    }
    // Center control bonus
    if(endRow >= 2 && endRow <= 5 && endCol >= 2 && endCol <= 5) {
        score += 2; // Add a score for control of the center
        if(endRow >= 3 && endRow <= 4 && endCol >= 3 && endCol <= 4) {
            score += 2;
        }
    }
    // Net threats/dangers
    int threatBalance  = moveMakeOrInThreats(move, source);
    score += threatBalance ;

    // Pawn promotion and advancement bonuses
    if(source->getType() == PAWN) {
        if(endRow == 0 || endRow == 7) {
            score += 8; // Promotion
        }
        // Advancement
        int advancement = (source->getColor() == WHITE) ? endRow - startRow : startRow - endRow;
        if(advancement > 0) {
            score += advancement; // More points for advancing further
        }
    }

    // Development bonus: first move for knights/bishops
    if(source->getType() == KNIGHT || source->getType() == BISHOP) {
        if((source->getColor() == WHITE && startRow == 0) ||
           (source->getColor() == BLACK && startRow == 7)) {
            score += 3;
        }
    }
    // Penalty for early king moves ("unsafe king")
    if(source->getType() == KING) {
        if((source->getColor() == WHITE && startRow == 0) ||
           (source->getColor() == BLACK && startRow == 7)) {
            score -= 3;
        }
    }
    // Activity bonus: reward moves that increase mobility from destination
    int mobilityBonus = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(tempBoard->isValidMove(endRow, endCol, i, j) > Constants::CHECK_STATUS) {
                mobilityBonus++;
            }
        }
    }
    score += mobilityBonus / 4;

    return score;
}

// Minimax-like move evaluation: recursively score moves for both sides
int EvaluateAllMoves::evaluateOneMove(Move* move, int depth) {
    int bestOpponentScore = INT_MIN; // Initialize to a very low value
    auto [startRow, startCol] = move->getStartPosition();
    auto [endRow, endCol] = move->getEndPosition();

    Piece* source = tempBoard->getPieceWithePermission(startRow,startCol);
    Piece* target = tempBoard->getPieceWithePermission(endRow, endCol);

    tempBoard->makeMove(source, startRow, startCol, endRow, endCol);

    int score = getMoveScore(move, target, source); // Get the score for the move

    if(depth > 1) {
        tempBoard->changeTurn();
        vector<std::unique_ptr<Move>> opponentMoves = getAllValidMoves();

        // Evaluate opponent's moves
        for (auto& opponentMove: opponentMoves) {
            int rivalScore = evaluateOneMove(opponentMove.get(), depth - 1);
            bestOpponentScore = max(bestOpponentScore, rivalScore);
        }
        tempBoard->changeTurn();

        // Subtract opponent's best possible counter
        if(bestOpponentScore != INT_MIN) {
            score -= bestOpponentScore;
        }
    }

    tempBoard->undoMove(source, target, startRow, startCol, endRow, endCol);
    return score;
}
