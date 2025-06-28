//
// Created by omer on 4/13/2025.
//

#include "King.h"

/**
 * Constructor for the King class.
 * Initializes a king at the given position with the specified color.
 *
 * @param i The row position of the king.
 * @param j The column position of the king.
 * @param color The color of the king (WHITE or BLACK).
 */
King::King(int i, int j, PieceColor color) : Piece(i, j, color, KING) {}


bool King::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // A king can only move one square in any direction: vertically, horizontally, or diagonally.
    // Calculate the difference between the coordinates
    int dy = std::abs(endRow - startRow);
    int dx = std::abs(endCol - startCol);

    // A king can only move one square in each direction
    if ((dx == 2 && dy == 0) && startCol == 4 && (endCol == 6 || endCol == 2) && !board.King_in_check(getColor())) {
        if (getColor()) {
            if (board.whiteKingCanCastle(endCol == 6)) {
                return true;
            }
        }
        else {
            if (board.blackKingCanCastle(endCol == 6)) {
                return true;
            }
        }
    }
    if ((dx <= 1 && dy <= 1) && (dx + dy > 0)) {
        return true;
    }
    return false;
}


bool King::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // Always returns false, as a king cannot threaten another king as a result of his own move.
    return false;
}

/**
* The king is the most valuable piece but has a value of 0 in terms of scoring
* because it cannot be captured like other pieces.
* and check is calculate in a different place using the move status.
*/
int King::getValue() const {
    return 0;
}

Piece *King::clone() const {
    return new King(*this);
}
