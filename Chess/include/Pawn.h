//
// Created by omer on 4/14/2025.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"


class Pawn : public Piece{
    bool hasMoved; // Did the soldier move in the past?
public:
    Pawn(int i, int j, PieceColor color);
    ~Pawn() override = default;


    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override;

    // Check if the soldier has reached the last line (Promotion)
    bool isPromotion(int x) const override;

    // Update the soldier's status
    void setHasMoved();

    bool isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const override;
};


#endif //CHESS_PAWN_H
