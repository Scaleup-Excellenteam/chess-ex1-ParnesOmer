//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "Piece.h"

/**
 * The Knight class represents a knight piece in the game of chess.
 * It inherits from the Piece base class and implements specific rules for knight movement and threats.
 */
class Knight : public Piece{
public:
    Knight(int i, int j, PieceColor color);
    ~Knight() override = default;

    /// Checks if the knight's move is valid according to chess rules.
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    /// Determines if the knight is threatening the enemy king's position.
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    /// Gets the value of the Knight piece.
    int getValue() const override;
    /// Clones the Knight piece.
    Piece* clone() const override;
};

#endif //CHESS_KNIGHT_H
