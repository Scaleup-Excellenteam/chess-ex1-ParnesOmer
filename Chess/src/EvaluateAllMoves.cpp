////
//// Created by omer on 5/13/2025.
////


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

    // Launch a job for each move with separate board copy per thread
    for (auto& move : allValidMoves) {
        Move moveCopy = *move;
        auto job = [moveCopy, &resultQueue, &stopFlag, originalBoard = this->board, depth = this->depth]() mutable {
            if (stopFlag.load()) return;

            // Create separate evaluator for this thread
            EvaluateAllMoves evaluator(depth, originalBoard);
            int score = evaluator.minimaxEvaluateMove(&moveCopy, depth);
            moveCopy.setScore(score);

            // Early exit if a "winning" move is found
            if (score >= Constants::HIGH_SCORE_THRESHOLD) { // Mate or near-mate score
                stopFlag.store(true);
            }

            resultQueue.push(std::make_unique<Move>(moveCopy));
        };
        futures.push_back(pool.enqueue(job));
    }

    // Wait for all threads
    for (auto& f : futures) {
        f.get();
    }

    // Collect results into a priority queue
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
    allValidMoves.reserve(50); // Pre-allocate typical number of moves

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

    // Sort moves for better alpha-beta pruning
    sortMovesByPriority(allValidMoves);
    return allValidMoves;
}

// Sort moves for better alpha-beta pruning
void EvaluateAllMoves::sortMovesByPriority(vector<std::unique_ptr<Move>>& moves) {
    std::sort(moves.begin(), moves.end(), [this](const std::unique_ptr<Move>& a, const std::unique_ptr<Move>& b) {
        int scoreA = getMoveOrderingScore(a.get());
        int scoreB = getMoveOrderingScore(b.get());
        return scoreA > scoreB; // Higher score first
    });
}

// Give priority scores for move ordering
int EvaluateAllMoves::getMoveOrderingScore(Move* move) {
    auto [startRow, startCol] = move->getStartPosition();
    auto [endRow, endCol] = move->getEndPosition();

    Piece* source = (*tempBoard)[startRow][startCol];
    Piece* target = (*tempBoard)[endRow][endCol];

    int score = 0;

    // Prioritize captures
    if (target != nullptr) {
        score += target->getValue() * 100 - source->getValue(); // MVV-LVA
    }

    // Prioritize checks
    int moveStatus = move->getMoveStatus();
    bool isCheck = std::find(
            std::begin(Constants::MADE_CHECK_CODES),
            std::end(Constants::MADE_CHECK_CODES),
            moveStatus) != std::end(Constants::MADE_CHECK_CODES);

    if (isCheck) {
        score += 50;
    }

    // Prioritize center moves
    if (endRow >= 3 && endRow <= 4 && endCol >= 3 && endCol <= 4) {
        score += 10;
    }

    return score;
}

// Get positional bonus for a piece at a specific position
int EvaluateAllMoves::getPositionalBonus(Piece* piece, int row, int col, bool isEndgame) {
    int bonus = 0;
    bool isMyPiece = (piece->getColor() == board.getTurn());

    if(piece->getType() == PAWN) {
        // Pawn advancement (max 0.7 points for reaching 7th rank)
        int advancement = (piece->getColor() == WHITE) ? row : (7 - row);
        bonus += isMyPiece ? (advancement * 10) : -(advancement * 10); // 0.1 per rank

        // Near promotion bonus
        if((piece->getColor() == WHITE && row == 6) ||
           (piece->getColor() == BLACK && row == 1)) {
            bonus += isMyPiece ? 200 : -200; // 2 points for near promotion
        }

        // Doubled pawn penalty
        int frontRow = (piece->getColor() == WHITE) ? row + 1 : row - 1;
        if(frontRow >= 0 && frontRow < 8) {
            Piece* blockingPiece = (*tempBoard)[frontRow][col];
            if(blockingPiece && blockingPiece->getType() == PAWN &&
               blockingPiece->getColor() == piece->getColor()) {
                bonus += isMyPiece ? -50 : 50; // 0.5 penalty for doubled pawns
            }
        }
    }
    else if(piece->getType() == KNIGHT || piece->getType() == BISHOP) {
        // Development bonus
        bool isDeveloped = !((piece->getColor() == WHITE && row == 0) ||
                             (piece->getColor() == BLACK && row == 7));
        if(isDeveloped) {
            bonus += isMyPiece ? 30 : -30; // 0.3 points for development
        }

        // Center control for knights
        if(piece->getType() == KNIGHT && row >= 2 && row <= 5 && col >= 2 && col <= 5) {
            bonus += isMyPiece ? 20 : -20; // 0.2 points for centralized knight
        }
    }
    else if(piece->getType() == KING) {
        if(isEndgame) {
            // Active king in endgame
            if(row >= 2 && row <= 5 && col >= 2 && col <= 5) {
                bonus += isMyPiece ? 50 : -50; // 0.5 points for active king
            }
        } else {
            // King safety in middlegame
            if((piece->getColor() == WHITE && row == 0) ||
               (piece->getColor() == BLACK && row == 7)) {
                if(col <= 2 || col >= 5) {
                    bonus += isMyPiece ? 20 : -20; // 0.2 points for castled king
                }
            }
        }
    }

    // Small center control bonus for all pieces
    if(row >= 2 && row <= 5 && col >= 2 && col <= 5) {
        bonus += isMyPiece ? 5 : -5; // 0.05 points for center presence
        if(row >= 3 && row <= 4 && col >= 3 && col <= 4) {
            bonus += isMyPiece ? 10 : -10; // Extra 0.1 for strong center
        }
    }

    return bonus;
}

// King safety with caching
int EvaluateAllMoves::getKingSafetyBonus(const vector<std::unique_ptr<Move>>& currentPlayerMoves,
                                         const vector<std::unique_ptr<Move>>& enemyPlayerMoves) {
    int bonus = 0;
    int threatsOnMyKing = 0;
    int threatsOnEnemyKing = 0;

    // Count threats more efficiently
    for (const auto& move : currentPlayerMoves) {
        int codeResponse = move->getMoveStatus();
        if (std::find(std::begin(Constants::MADE_CHECK_CODES),
                      std::end(Constants::MADE_CHECK_CODES),
                      codeResponse) != std::end(Constants::MADE_CHECK_CODES)) {
            threatsOnEnemyKing++;
        }
    }

    for (const auto& move : enemyPlayerMoves) {
        int codeResponse = move->getMoveStatus();
        if (std::find(std::begin(Constants::MADE_CHECK_CODES),
                      std::end(Constants::MADE_CHECK_CODES),
                      codeResponse) != std::end(Constants::MADE_CHECK_CODES)) {
            threatsOnMyKing++;
        }
    }

    // Reasonable check values
    bonus += threatsOnEnemyKing * 100; // 1 point per check threat
    bonus -= threatsOnMyKing * 100;   // -1 point per threat on my king

    return bonus;
}

// Compute score with caching and early exit
int EvaluateAllMoves::evaluateBoardPosition(Move *move, Piece *target, Piece *source) {
    int score = 0;
    int codeResponse = move->getMoveStatus();

    bool madeCheck = std::find(
            std::begin(Constants::MADE_CHECK_CODES),
            std::end(Constants::MADE_CHECK_CODES),
            codeResponse) != std::end(Constants::MADE_CHECK_CODES);

    bool inCheck = tempBoard->King_in_check(tempBoard->getTurn());

    // Check for mate/draw - but only generate moves once
    vector<std::unique_ptr<Move>> currentPlayerMoves = getAllValidMoves();
    if (currentPlayerMoves.empty()) {
        if (inCheck) {
            return (tempBoard->getTurn() == board.getTurn()) ? -10000 : 10000; // Mate score
        } else {
            return 0; // Draw
        }
    }

    // Count pieces once
    int totalPieces = 0;
    int materialScore = 0;

    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            Piece* piece = (*tempBoard)[r][c];
            if(piece) {
                totalPieces++;
                int pieceValue = piece->getValue() * 100; // Convert to centi-points
                if (piece->getColor() == board.getTurn()) {
                    materialScore += pieceValue;
                } else {
                    materialScore -= pieceValue;
                }

                // Add positional bonus
                score += getPositionalBonus(piece, r, c, totalPieces <= 10);
            }
        }
    }

    score += materialScore;

    tempBoard->changeTurn();
    vector<std::unique_ptr<Move>> opponentMoves = getAllValidMoves();
    if (opponentMoves.empty()) {
        if (madeCheck) {
            tempBoard->changeTurn();
            return (tempBoard->getTurn() == board.getTurn()) ? 10000 : -10000; // Mate score
        }
        else {
            tempBoard->changeTurn();
            return 0;
        }
    }
    tempBoard->changeTurn();
    // Mobility and king safety
    size_t myMobility = currentPlayerMoves.size();
    size_t opponentMobility = opponentMoves.size();

    // King safety
    score += getKingSafetyBonus(currentPlayerMoves, opponentMoves);

    // Mobility bonus
    int mobilityWeight = (totalPieces <= 10) ? 2 : 1; // Less important in opening
    score += static_cast<int>(myMobility - opponentMobility) * mobilityWeight;

    return score;
}

// Minimax evaluation with alpha-beta pruning
int EvaluateAllMoves::minimaxEvaluateMove(Move* move, int depth, int alpha, int beta) {
    auto [startRow, startCol] = move->getStartPosition();
    auto [endRow, endCol] = move->getEndPosition();

    Piece* source = tempBoard->getPieceWithePermission(startRow, startCol);
    Piece* target = tempBoard->getPieceWithePermission(endRow, endCol);

    tempBoard->makeMove(source, startRow, startCol, endRow, endCol);

    int score = 0;

    if(depth <= 1) {
        score = evaluateBoardPosition(move, target, source);
    }
    else {
        tempBoard->changeTurn();
        vector<std::unique_ptr<Move>> opponentMoves = getAllValidMoves();

        if(opponentMoves.empty()) {
            // Handle mate/stalemate at deeper levels
            bool inCheck = tempBoard->King_in_check(tempBoard->getTurn());
            if(inCheck) {
                score = (tempBoard->getTurn() == board.getTurn()) ? -10000 + depth : 10000 - depth;
            } else {
                score = 0; // Stalemate
            }
        }
        else if(tempBoard->getTurn() == board.getTurn()) {
            // Maximizing player
            int maxEval = INT_MIN;
            for (auto &opponentMove: opponentMoves) {
                int evalScore = minimaxEvaluateMove(opponentMove.get(), depth - 1, alpha, beta);
                maxEval = max(maxEval, evalScore);
                alpha = max(alpha, evalScore);

                if(beta <= alpha) {
                    break; // Beta cutoff
                }
            }
            score = maxEval;
        }
        else {
            // Minimizing player
            int minEval = INT_MAX;
            for (auto& opponentMove: opponentMoves) {
                int evalScore = minimaxEvaluateMove(opponentMove.get(), depth - 1, alpha, beta);
                minEval = min(minEval, evalScore);
                beta = min(beta, evalScore);

                if(beta <= alpha) {
                    break; // Alpha cutoff
                }
            }
            score = minEval;
        }

        tempBoard->changeTurn();
    }

    tempBoard->undoMove(source, target, startRow, startCol, endRow, endCol);
    return score;
}
