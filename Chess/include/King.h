//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"

/**
 * The King class represents a king piece in the game of chess.
 * It inherits from the Piece base class and implements specific rules for the king's movement and threats.
 */
class King : public Piece{
public:
    King(int i, int j, PieceColor color);
    ~King() override = default;

    /// Checks if the king's move is valid according to chess rules.
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    /// Determines if the king is threatening the enemy king's position.
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    /// Gets the value of the King piece.
    int getValue() const override;
    /// Clones the King piece.
    Piece* clone() const override;
};

#endif //CHESS_KING_H
