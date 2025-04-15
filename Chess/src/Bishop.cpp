//
// Created by omer on 4/13/2025.
//

#include "Bishop.h"

Bishop::Bishop(int i, int j, PieceColor color) : Piece(i, j, color) {
    type = BISHOP;
}

bool Bishop::isValidMove(int startX, int startY, int endX, int endY, const Board &board) const {
    // Calculate the difference between the coordinates
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    //Checks if the move is diagonal
    if (dx != dy) {
        return false;
    }
    // Check if the path is free
    int stepX = (endX > startX) ? 1 : -1; // Direction of movement on the X axis
    int stepY = (endY > startY) ? 1 : -1; // Direction of movement on the Y axis

    int next_x = startX + stepX;
    int next_y = startY + stepY;
    while(next_x != endX && next_y != endY){
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

bool Bishop::isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const {
    int dx = abs(EnemyKingX - myX);
    int dy = abs(EnemyKingY - myY);

    //Checks if the move is diagonal
    if (dx == dy) {
        return true;
    }
    return false;
}