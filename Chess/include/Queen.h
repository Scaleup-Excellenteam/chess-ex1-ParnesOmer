//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "Piece.h"


class Queen : public Piece{
public:
    Queen(int i, int j, PieceColor color) : Piece(i, j, color) {}
    ~Queen() = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override {

    }

};


#endif //CHESS_QUEEN_H
