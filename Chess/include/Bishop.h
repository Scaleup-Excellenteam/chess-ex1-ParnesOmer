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
    /**
     * Default destructor for the Bishop class.
     * Since the Bishop class does not allocate dynamic resources, the default destructor is sufficient.
     */
    ~Bishop() override = default;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const override;

    bool isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const override;

    /**
     * Gets the value of the Bishop piece.
     *
     * @return
     */
    int getValue() const override {
        return 3;
    }
    /**
     * Clones the Bishop object.
     * @return A pointer to the cloned Bishop object.
     */
    Piece* clone() const override {
        return new Bishop(*this);
    }
};


#endif //CHESS_BISHOP_H
