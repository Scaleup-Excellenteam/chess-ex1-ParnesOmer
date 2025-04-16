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
    /**
     * Default destructor for the Knight class.
     * Since the Knight class does not allocate dynamic resources, the default destructor is sufficient.
     */
    ~Knight() override = default;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;

    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;
};


#endif //CHESS_KNIGHT_H
