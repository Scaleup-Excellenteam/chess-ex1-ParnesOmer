//
// Created by omer on 4/13/2025.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"

/**
 * The Queen class represents a queen piece in the game of chess.
 * It inherits from the Piece base class and uses the logic of both the Rook and Bishop
 * to implement the queen's movement and threat rules.
 */
class Queen : public Piece{
public:
    Queen(int i, int j, PieceColor color);
    ~Queen() override = default;

    /// Checks if the queen's move is valid according to chess rules.
    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    /// Determines if the queen is threatening the enemy king's position.
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    /// Gets the value of the Queen piece.
    int getValue() const override;
    /// Clones the Queen piece.
    Piece* clone() const override;
};

#endif //CHESS_QUEEN_H
