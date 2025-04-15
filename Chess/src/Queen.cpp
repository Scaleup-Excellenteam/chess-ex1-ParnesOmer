//
// Created by omer on 4/13/2025.
//

#include "Queen.h"

Queen::Queen(int i, int j, PieceColor color) : Piece(i, j, color) {
    type = QUEEN;
}

bool Queen::isValidMove(int startX, int startY, int endX, int endY, const Board &board) const {
    // Create temporary Rook and Bishop objects
    Rook queen_as_rook(startX, startY, this->getColor());
    Bishop queen_as_bishop(startX, startY, this->getColor());
    if(queen_as_rook.isValidMove(startX, startY, endX, endY, board) ||
       queen_as_bishop.isValidMove(startX, startY, endX, endY, board)){
        return true;
    }
    return false;
}

bool Queen::isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const {
    Rook queen_as_rook(myX, myY, this->getColor());
    Bishop queen_as_bishop(myX, myY, this->getColor());

    if(queen_as_rook.isThreat(myX, myY, EnemyKingX, EnemyKingY) ||
       queen_as_bishop.isThreat(myX, myY, EnemyKingX, EnemyKingY)){
        return true;
    }
    return false;
}
