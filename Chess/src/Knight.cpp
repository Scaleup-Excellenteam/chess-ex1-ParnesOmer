//
// Created by omer on 4/13/2025.
//

#include "Knight.h"

Knight::Knight(int i, int j, PieceColor color) : Piece(i, j, color) {
    type = KNIGHT;
}

bool Knight::isValidMove(int startX, int startY, int endX, int endY, const Board &board) const {
    if((abs(endX - startX) == 2 && abs(endY - startY) == 1) ||
       (abs(endX - startX) == 1 && abs(endY - startY) == 2)){
        //Checks whether the move was legal in an L-shape
        return true;
    }
    return false;
}

bool Knight::isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const {
    if((abs(EnemyKingX - myX) == 2 && abs(EnemyKingY - myY) == 1) ||
       (abs(EnemyKingX - myX) == 1 && abs(EnemyKingY - myY) == 2)){
        //Checks whether the move was legal in an L-shape
        return true;
    }
    return false;
}