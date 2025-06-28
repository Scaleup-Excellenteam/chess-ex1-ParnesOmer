//
// Created by omer on 4/13/2025.
//

#include "Bishop.h"

/**
 * Constructor for the Bishop class.
 * Initializes a bishop at the given position with the specified color.
 *
 * @param i The row position of the bishop.
 * @param j The column position of the bishop.
 * @param color The color of the bishop (WHITE or BLACK).
 */
Bishop::Bishop(int i, int j, PieceColor color) : Piece(i, j, color, BISHOP) {}


bool Bishop::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // Calculate the difference between the coordinates
    int dx = std::abs(endRow - startRow);
    int dy = std::abs(endCol - startCol);

    //Checks if the move is diagonal
    if (dx != dy) {
        return false;
    }
    // Check if the path is free
    int stepX = (endRow > startRow) ? 1 : -1; // Direction of movement on the X axis
    int stepY = (endCol > startCol) ? 1 : -1; // Direction of movement on the Y axis

    int next_x = startRow + stepX;
    int next_y = startCol + stepY;
    while(next_x != endRow && next_y != endCol){
        if (board.getPiece(next_x, next_y) != nullptr){
            // There is a piece on the way
            return false;
        }
        next_x += stepX;
        next_y += stepY;
    }

    // If we passed all the tests, the move is legal
    return true;
}


bool Bishop::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // A bishop threatens the king if the king is in any diagonal path from the bishop.
    int dx = std::abs(EnemyKingRow - myRow);
    int dy = std::abs(EnemyKingCol - myCol);

    //Checks if the move is diagonal
    return (dx == dy);
}

int Bishop::getValue() const {
    return Constants::BISHOP_VALUE;
}

Piece *Bishop::clone() const {
    return new Bishop(*this);
}
