//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"


class King : public Piece{
public:
    King(int i, int j, PieceColor color) : Piece(i, j, color) {}
    ~King() = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override {
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

};


#endif //CHESS_KING_H
