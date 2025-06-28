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


bool Knight::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // A knight moves in an L-shape: two squares in one direction and one square in a perpendicular direction,
    // or one square in one direction and two squares in a perpendicular direction.

    if((std::abs(endRow - startRow) == 2 && std::abs(endCol - startCol) == 1) ||
       (std::abs(endRow - startRow) == 1 && std::abs(endCol - startCol) == 2)){
        return true;
    }
    return false;
}


bool Knight::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // A knight threatens the king if the king is in any of the squares the knight can move to in an L-shape.
    if((std::abs(EnemyKingRow - myRow) == 2 && std::abs(EnemyKingCol - myCol) == 1) ||
       (std::abs(EnemyKingRow - myRow) == 1 && std::abs(EnemyKingCol - myCol) == 2)){
        // The move is in an L-shape to the enemy king.
        return true;
    }
    return false;
}

int Knight::getValue() const {
    return Constants::KNIGHT_VALUE;
}

Piece *Knight::clone() const {
    return new Knight(*this);
}
