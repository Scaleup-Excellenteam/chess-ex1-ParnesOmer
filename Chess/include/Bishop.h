//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "Piece.h"


class Bishop : public Piece{
public:
    Bishop(int i, int j, PieceColor color) : Piece(i, j, color) {}
    ~Bishop() = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override {
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
};


#endif //CHESS_BISHOP_H
