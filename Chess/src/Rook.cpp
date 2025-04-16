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

/**
 * Checks if the rook's move is valid according to chess rules.
 * The rook can move any number of squares along a row or column, as long as the path is clear.
 *
 * @param startRow The starting row of the rook.
 * @param startCol The starting column of the rook.
 * @param endRow The target row of the rook.
 * @param endCol The target column of the rook.
 * @param board The current state of the chessboard.
 * @return True if the move is valid, false otherwise.
 */
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

/**
 * Determines if the rook is threatening the enemy king's position.
 * The rook threatens the king if they are in the same row or column.
 *
 * @param myRow The current row of the rook.
 * @param myCol The current column of the rook.
 * @param EnemyKingRow The row position of the enemy king.
 * @param EnemyKingCol The column position of the enemy king.
 * @return True if the rook is threatening the enemy king, false otherwise.
 */
bool Rook::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    return (myRow == EnemyKingRow || myCol == EnemyKingCol);
}

