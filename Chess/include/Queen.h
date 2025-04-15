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
    Queen(int i, int j, PieceColor color);
    ~Queen() override = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override;

    bool isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const override;

};


#endif //CHESS_QUEEN_H
