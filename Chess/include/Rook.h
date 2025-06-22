//
// Created by omer on 4/3/2025.
//

#ifndef CHESS_EX1_PARNESOMER_MAIN_ROOK_H
#define CHESS_EX1_PARNESOMER_MAIN_ROOK_H
#include "Piece.h"

/**
 * The Rook class represents a rook piece in the game of chess.
 * It inherits from the Piece base class and implements the specific movement and threat logic for a rook.
 */
class Rook : public Piece{
public:
    Rook(int i, int j, PieceColor color);
    ~Rook() override = default;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    /// Determines if the rook is threatening the enemy king's position.
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    /// Gets the value of the Rook piece.
    int getValue() const override;
    /// Clones the Rook piece.
    Piece* clone() const override;
};

#endif //CHESS_EX1_PARNESOMER_MAIN_ROOK_H
