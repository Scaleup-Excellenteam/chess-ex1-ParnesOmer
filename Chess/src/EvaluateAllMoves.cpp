//
// Created by omer on 5/13/2025.
//

#include "EvaluateAllMoves.h"


/// Constructor for EvaluateAllMoves. Initializes the evaluator for a given board and search depth.
EvaluateAllMoves::EvaluateAllMoves(int depth, const Board& board) : depth(depth), board(board){
    tempBoard = new Board(board); // Create a copy of the board
}

/// Destructor for EvaluateAllMoves. Cleans up the temporary board.
EvaluateAllMoves::~EvaluateAllMoves() {
    delete tempBoard;
}

/// Generates all valid moves for the current player, evaluates their scores, and returns them.
vector<Move*> EvaluateAllMoves::evaluateAllMoves() {
    vector<Move*> allValidMoves = getAllValidMoves(); // Get all valid moves

    for (Move* move : allValidMoves) { // Iterate through all valid moves
        move->setScore(evaluateOneMove(move, depth)); // Evaluate each move with a depth of 3
    }

    return allValidMoves;
}

/// Returns all valid (legal) moves for the current player from the current board position.
vector<Move*> EvaluateAllMoves::getAllValidMoves() {
    vector<Move*> allValidMoves;
    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* pieceSource = (*tempBoard)[i][j];
            if(pieceSource != nullptr && pieceSource->getColor() == tempBoard->getTurn()) {
                for (int r = 0; r < 8; ++r) {
                    for (int c = 0; c < 8; ++c) {
                        int moveStatus = tempBoard->isValidMove(i, j, r, c);
                        if(moveStatus > 40){
                            // The move is valid
                            allValidMoves.emplace_back(new Move(i, j, r, c, moveStatus)); // Add the move to the list
                        }
                    }
                }
            }
        }
    }
    return allValidMoves;
}

/// Calculates the net threat impact of a move
int EvaluateAllMoves::moveMakeOrInThreats(Move* move, Piece* movedPiece) {
    auto [endRow, endCol] = move->getEndPosition();

    if(!movedPiece) return false;

    int threats = 0;
    int dangers = 0;

    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Piece* enemyPiece = (*tempBoard)[i][j];
            if(enemyPiece && enemyPiece->getColor() != movedPiece->getColor()) {
                if(tempBoard->isValidMove(endRow, endCol, i, j) > 40) {
                    if(enemyPiece->getValue() > movedPiece->getValue()) {
                        threats += enemyPiece->getValue();
                    }
                }
                tempBoard->changeTurn();
                if(tempBoard->isValidMove(i, j, endRow, endCol) > 40) {
                    if(enemyPiece->getValue() < movedPiece->getValue()) {
                        dangers += movedPiece->getValue();
                    }
                }
                tempBoard->changeTurn();
            }
        }
    }
    // return the difference between threats and dangers
    return threats - dangers;
}

/// Calculates the score of a move based on various factors such as:
int EvaluateAllMoves::getMoveScore(Move *move, Piece *target, Piece *source) {
    auto [endRow, endCol] = move->getEndPosition(); // Get the end position of the move
    int score = 0;

    if(move->getMoveStatus() == 41){
        score += 7; // Add a score for putting the rival king in check
    }
    if(target){ // If the target square contains a piece, add its value to the score
        score += target->getValue(); // Add the value of the captured piece
    }
    if(endRow >= 2 && endRow <= 5 && endCol >= 2 && endCol <= 5) {
        score += 2; // Add a score for control of the center
    }
    // check the balance of the threats that the move creates(can be negative).
    int balance = moveMakeOrInThreats(move, source);
    score += balance;

    // Add a score for pawn promotion
    if(source->getType() == PAWN) {
        if(endRow == 0 || endRow == 7) {
            score += 5;
        }
    }
    return score;
}

/// Recursively evaluates a move to a given depth using a simple minimax approach.
int EvaluateAllMoves::evaluateOneMove(Move* move, int depth) {
    int bestOpponentScore = INT_MIN; // Initialize to a very low value
    auto [startRow, startCol] = move->getStartPosition();
    auto [endRow, endCol] = move->getEndPosition();

    Piece* source = tempBoard->getPieceWithePermission(startRow,startCol);
    Piece* target = tempBoard->getPieceWithePermission(endRow, endCol);

    tempBoard->makeMove(source, startRow, startCol, endRow, endCol);

    int score =  getMoveScore(move, target, source); // Get the score for the move

    if(depth > 1) {
        tempBoard->changeTurn();

        vector<Move*> opponentMoves = getAllValidMoves();

        // Evaluate opponent's moves
        for (Move* opponentMove: opponentMoves) {
            int rivalScore = -evaluateOneMove(opponentMove, depth - 1);
            bestOpponentScore = max(bestOpponentScore, rivalScore);
        }
        for(Move* opponentMove: opponentMoves) {
            delete opponentMove; // Free memory for opponent moves
        }
        opponentMoves.clear(); // Clear the vector of opponent moves
        tempBoard->changeTurn();
    }

    tempBoard->undoMove(source, target, startRow, startCol, endRow, endCol); // Undo the move
    if(bestOpponentScore == INT_MIN) {
        bestOpponentScore = 0; // Skip if the move is invalid
    }
    return score + bestOpponentScore;
}
