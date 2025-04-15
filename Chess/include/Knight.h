//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "Piece.h"


class Knight : public Piece{
public:
    Knight(int i, int j, PieceColor color);
    ~Knight() override = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override;

    bool isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const override;
};


#endif //CHESS_KNIGHT_H
