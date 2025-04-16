//
// Created by omer on 4/13/2025.
//

#include "King.h"

/**
 * Constructor for the King class.
 * Initializes a king at the given position with the specified color.
 *
 * @param i The row position of the king.
 * @param j The column position of the king.
 * @param color The color of the king (WHITE or BLACK).
 */
King::King(int i, int j, PieceColor color) : Piece(i, j, color, KING) {}

/**
 * Checks if the king's move is valid according to chess rules.
 * A king can only move one square in any direction: vertically, horizontally, or diagonally.
 *
 * @param startRow The starting row of the king.
 * @param startCol The starting column of the king.
 * @param endRow The target row of the king.
 * @param endCol The target column of the king.
 * @param board The current state of the chessboard.
 * @return True if the move is valid, false otherwise.
 */
bool King::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // Calculate the difference between the coordinates
    int dx = abs(endRow - startRow);
    int dy = abs(endCol - startCol);

    // A king can only move one square in each direction
    if (dx > 1 || dy > 1) {
        return false;
    }
    return true;
}

/**
 * Determines if the king is threatening the enemy king's position.
 * According to chess rules, a king cannot directly threaten another king as a result of his own move.
 *
 * @param myRow The current row of the king.
 * @param myCol The current column of the king.
 * @param EnemyKingRow The row position of the enemy king.
 * @param EnemyKingCol The column position of the enemy king.
 * @return Always returns false, as a king cannot threaten another king as a result of his own move.
 */
bool King::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    return false;
}
