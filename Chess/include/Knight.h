//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "Piece.h"


class Knight : public Piece{
public:
    Knight(int i, int j, PieceColor color) : Piece(i, j, color) {}
    ~Knight() = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override {
        if((abs(endX - startX) == 2 && abs(endY - startY) == 1) ||
        (abs(endX - startX) == 1 && abs(endY - startY) == 2)){
            //Checks whether the move was legal in an L-shape
            return true;
        }
        return false;
    }
};


#endif //CHESS_KNIGHT_H
