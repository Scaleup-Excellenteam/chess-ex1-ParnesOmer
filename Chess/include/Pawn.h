//
// Created by omer on 4/14/2025.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

/**
 * The Pawn class represents a pawn piece in the game of chess.
 * It inherits from the Piece base class and implements the specific movement and threat logic for a pawn.
 */
class Pawn : public Piece{
public:
    Pawn(int i, int j, PieceColor color);
    ~Pawn() override = default;

    /// Checks if the pawn's move is valid according to chess rules.
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    /// Determines if the pawn is threatening the enemy king's position.
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;
    /// Checks if the pawn is making its first move.
    static bool isFirstMove(PieceColor color, int row);

    /// Gets the value of the Pawn piece.
    int getValue() const override;
    /// Clones the Pawn piece.
    Piece* clone() const override;
};

#endif //CHESS_PAWN_H
