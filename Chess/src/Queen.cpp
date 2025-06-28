//
// Created by omer on 4/13/2025.
//

#include "Queen.h"

/**
 * Constructor for the Queen class.
 * Initializes a queen at the given position with the specified color.
 *
 * @param i The row position of the queen.
 * @param j The column position of the queen.
 * @param color The color of the queen (WHITE or BLACK).
 */
Queen::Queen(int i, int j, PieceColor color) : Piece(i, j, color, QUEEN) {}


bool Queen::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // This function uses the logic of both the rook and the bishop to validate the move.
    // Create temporary Rook and Bishop objects
    Rook queen_as_rook(startRow, startCol, this->getColor());
    Bishop queen_as_bishop(startRow, startCol, this->getColor());
    if(queen_as_rook.isValidMove(startRow, startCol, endRow, endCol, board) ||
       queen_as_bishop.isValidMove(startRow, startCol, endRow, endCol, board)){
        return true;
    }
    return false;
}


bool Queen::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // This function uses the logic of both the rook and the bishop to determine if the queen threatens the enemy king.
    Rook queen_as_rook(myRow, myCol, this->getColor());
    Bishop queen_as_bishop(myRow, myCol, this->getColor());

    if(queen_as_rook.isThreat(myRow, myCol, EnemyKingRow, EnemyKingCol) ||
       queen_as_bishop.isThreat(myRow, myCol, EnemyKingRow, EnemyKingCol)){
        return true;
    }
    return false;
}

int Queen::getValue() const {
    return Constants::QUEEN_VALUE;
}


Piece *Queen::clone() const {
    return new Queen(*this);
}
