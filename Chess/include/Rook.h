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
    /**
     * Default destructor for the Rook class.
     * Since the Rook class does not allocate dynamic resources, the default destructor is sufficient.
     */
    ~Rook() override = default;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;

    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;
};

#endif //CHESS_EX1_PARNESOMER_MAIN_ROOK_H
