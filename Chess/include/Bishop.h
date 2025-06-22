//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "Piece.h"

/**
 * The Bishop class represents a bishop piece in the game of chess.
 * It inherits from the Piece base class and implements specific rules for bishop movement and threats.
 */
class Bishop : public Piece{
public:
    Bishop(int i, int j, PieceColor color);
    ~Bishop() override = default;

    /// Checks if the bishop's move is valid according to chess rules.
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    /// Determines if the bishop is threatening the enemy king's position.
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    /// Gets the value of the Bishop piece.
    int getValue() const override;
    /// Clones the Bishop piece.
    Piece* clone() const override;
};

#endif //CHESS_BISHOP_H
