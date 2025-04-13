//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"


class Queen : public Piece{
public:
    Queen(int i, int j, PieceColor color) : Piece(i, j, color) {}
    ~Queen() = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override {
        // Create temporary Rook and Bishop objects
        Rook queen_as_rook(startX, startY, this->getColor());
        Bishop queen_as_bishop(startX, startY, this->getColor());

        return queen_as_rook.isValidMove(startX, startY, endX, endY, board) ||
                queen_as_bishop.isValidMove(startX, startY, endX, endY, board);
    }

};


#endif //CHESS_QUEEN_H
