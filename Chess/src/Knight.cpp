//
// Created by omer on 4/13/2025.
//

#include "Knight.h"

/**
 * Constructor for the Knight class.
 * Initializes a knight at the given position with the specified color.
 *
 * @param i The row position of the knight.
 * @param j The column position of the knight.
 * @param color The color of the knight (WHITE or BLACK).
 */
Knight::Knight(int i, int j, PieceColor color) : Piece(i, j, color, KNIGHT) {}

/**
 * Checks if the knight's move is valid according to chess rules.
 * A knight moves in an L-shape: two squares in one direction and one square in a perpendicular direction,
 * or one square in one direction and two squares in a perpendicular direction.
 *
 * @param startRow The starting row of the knight.
 * @param startCol The starting column of the knight.
 * @param endRow The target row of the knight.
 * @param endCol The target column of the knight.
 * @param board The current state of the chessboard.
 * @return True if the move is valid, false otherwise.
 */
bool Knight::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    if((abs(endRow - startRow) == 2 && abs(endCol - startCol) == 1) ||
       (abs(endRow - startRow) == 1 && abs(endCol - startCol) == 2)){
        // The move is in an L-shape
        return true;
    }
    return false;
}

/**
 * Determines if the knight is threatening the enemy king's position.
 * A knight threatens the king if the king is in any of the squares the knight can move to in an L-shape.
 *
 * @param myRow The current row of the knight.
 * @param myCol The current column of the knight.
 * @param EnemyKingRow The row position of the enemy king.
 * @param EnemyKingCol The column position of the enemy king.
 * @return True if the knight is threatening the enemy king, false otherwise.
 */
bool Knight::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    if((abs(EnemyKingRow - myRow) == 2 && abs(EnemyKingCol - myCol) == 1) ||
       (abs(EnemyKingRow - myRow) == 1 && abs(EnemyKingCol - myCol) == 2)){
        // The move is in an L-shape to the enemy king.
        return true;
    }
    return false;
}