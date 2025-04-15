//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "Piece.h"


class Bishop : public Piece{
public:
    Bishop(int i, int j, PieceColor color);
    ~Bishop() override = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override;

    bool isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const override;
};


#endif //CHESS_BISHOP_H
