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
    /**
     * Default destructor for the King class.
     * Since the King class does not allocate dynamic resources, the default destructor is sufficient.
     */
    ~King() override = default;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;
    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

};


#endif //CHESS_KING_H
