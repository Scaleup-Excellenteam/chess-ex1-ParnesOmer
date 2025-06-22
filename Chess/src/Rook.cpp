//
// Created by omer on 4/3/2025.
//

#include "../include/Rook.h"

/**
 * Constructor for the Rook class.
 * Initializes a rook at the given position with the specified color.
 *
 * @param i The row position of the rook.
 * @param j The column position of the rook.
 * @param color The color of the rook (WHITE or BLACK).
 */
Rook::Rook(int i, int j, PieceColor color) : Piece(i, j, color, ROOK){}


bool Rook::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // Check if the path is free
    if (startRow == endRow) {
        // Move along a column
        int step = (startCol < endCol) ? 1 : -1; // Direction of movement
        for (int y = startCol + step; y != endCol; y += step) {
            if (board.getPiece(startRow, y) != nullptr) {
                return false; // There is a tool on the way
            }
        }
    } else if (startCol == endCol) {
        // Move along row
        int step = (startRow < endRow) ? 1 : -1; // Direction of movement
        for (int x = startRow + step; x != endRow; x += step) {
            if (board.getPiece(x, startCol) != nullptr) {
                return false; // There is a tool on the way
            }
        }
    }else {
        // Check if the move is in the same row or column
        return false;
    }

    // If we passed the tests, the move is legal
    return true;
}


bool Rook::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // The rook threatens the king if they are in the same row or column.
    return (myRow == EnemyKingRow || myCol == EnemyKingCol);
}

int Rook::getValue() const {
    return Constants::ROOK_VALUE;
}

Piece *Rook::clone() const {
    return new Rook(*this);
}

