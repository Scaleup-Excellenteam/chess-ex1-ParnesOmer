//
// Created by omer on 4/3/2025.
//

#ifndef CHESS_EX1_PARNESOMER_MAIN_ROOK_H
#define CHESS_EX1_PARNESOMER_MAIN_ROOK_H
#include "Piece.h"


class Rook : public Piece{
public:
    Rook(int i, int j, PieceColor color);
    ~Rook() override = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override;

    bool isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const override;
};

#endif //CHESS_EX1_PARNESOMER_MAIN_ROOK_H
