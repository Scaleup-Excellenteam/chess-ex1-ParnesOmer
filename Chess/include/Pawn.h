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
    /**
     * Default destructor for the Pawn class.
     * Since the Pawn class does not allocate dynamic resources, the default destructor is sufficient.
     */
    ~Pawn() override = default;


    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;

    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    static bool isFirstMove(PieceColor color, int row);

    /**
     * Gets the value of the Pawn piece.
     *
     * @return
     */
    int getValue() const override {
        return 1;
    }
    /**
     * Clones the Pawn object.
     * @return A pointer to the cloned Pawn object.
     */
    Piece* clone() const override {
        return new Pawn(*this);
    }
};


#endif //CHESS_PAWN_H
