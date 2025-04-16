//
// Created by omer on 4/14/2025.
//

#include "Pawn.h"

/**
 * Constructor for the Pawn class.
 * Initializes a pawn at the given position with the specified color.
 *
 * @param i The row position of the pawn.
 * @param j The column position of the pawn.
 * @param color The color of the pawn (WHITE or BLACK).
 */
Pawn::Pawn(int i, int j, PieceColor color) : Piece(i, j, color, PAWN){}

/**
 * Validates if the pawn's move is legal according to chess rules.
 *
 * @param startRow The starting row of the pawn.
 * @param startCol The starting column of the pawn.
 * @param endRow The target row of the pawn.
 * @param endCol The target column of the pawn.
 * @param board The current state of the chessboard.
 * @return True if the move is valid, false otherwise.
 */
bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // Direction of movement (forward for white or backward for black)
    PieceColor myColor = this->getColor();
    int direction = (myColor == WHITE) ? 1 : -1;

    // Normal forward movement
    if (endRow == startRow + direction && startCol == endCol) {
        if ((board.getPiece(endRow, endCol) == nullptr)) {
            return true; // Free square
        }
    }

    // Initial movement two squares forward
    if(isFirstMove(myColor, startRow) &&
       (endRow == startRow + (2 * direction)) && (startCol == endCol) ) {
        if (board.getPiece(startRow + direction, startCol) == nullptr &&
            board.getPiece(endRow, endCol) == nullptr) {
            return true; // Both squares are free
        }
    }

    // Eating diagonally
    if (endRow == startRow + direction && abs(endCol - startCol) == 1) {
        const Piece* targetPiece = board.getPiece(endRow, endCol);
        if (targetPiece != nullptr && targetPiece->getColor() != this->getColor()) {
            return true; // Opponent's piece diagonally
        }
    }

    // If we did not meet any conditions, the move is illegal
    return false;
}

/**
 * Determines if the pawn is threatening the enemy king's position.
 *
 * @param myRow The current row of the pawn.
 * @param myCol The current column of the pawn.
 * @param EnemyKingRow The row position of the enemy king.
 * @param EnemyKingCol The column position of the enemy king.
 * @return True if the pawn is threatening the enemy king, false otherwise.
 */
bool Pawn::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // Direction of movement (forward for white or backward for black)
    int direction = (this->getColor() == WHITE) ? 1 : -1;
    // Eating diagonally
    if (EnemyKingRow == myRow + direction && abs(EnemyKingCol - myCol) == 1) {
        return true; // Opponent's piece diagonally
    }
    return false;
}

/**
 * Checks if the pawn is making its first move.
 *
 * @param color The color of the pawn (WHITE or BLACK).
 * @param row The current row of the pawn.
 * @return True if the pawn is in its starting position, false otherwise.
 */
bool Pawn::isFirstMove(PieceColor color, int row) {
    if(color == WHITE){
        return row == 1;
    }
    return row == 6;
}
