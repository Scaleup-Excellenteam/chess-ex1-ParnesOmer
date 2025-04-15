//
// Created by omer on 4/13/2025.
//

#include "King.h"

King::King(int i, int j, PieceColor color) : Piece(i, j, color) {
    type = KING;
}

bool King::isValidMove(int startX, int startY, int endX, int endY, const Board &board) const {
    // Calculate the difference between the coordinates
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    //Can only move one square in each direction
    //vertically, horizontally, or diagonally
    if (dx > 1 || dy > 1) {
        return false;
    }
    return true;
}

bool King::isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const {
    return false;
}
