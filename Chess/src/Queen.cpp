//
// Created by omer on 4/13/2025.
//

#include "Queen.h"

/**
 * Constructor for the Queen class.
 * Initializes a queen at the given position with the specified color.
 *
 * @param i The row position of the queen.
 * @param j The column position of the queen.
 * @param color The color of the queen (WHITE or BLACK).
 */
Queen::Queen(int i, int j, PieceColor color) : Piece(i, j, color, QUEEN) {}

/**
 * Checks if the queen's move is valid according to chess rules.
 * A queen can move any number of squares along a row, column, or diagonal as long as the path is clear.
 *
 * This function uses the logic of both the rook and the bishop to validate the move.
 *
 * @param startRow The starting row of the queen.
 * @param startCol The starting column of the queen.
 * @param endRow The target row of the queen.
 * @param endCol The target column of the queen.
 * @param board The current state of the chessboard.
 * @return True if the move is valid, false otherwise.
 */
bool Queen::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // Create temporary Rook and Bishop objects
    Rook queen_as_rook(startRow, startCol, this->getColor());
    Bishop queen_as_bishop(startRow, startCol, this->getColor());
    if(queen_as_rook.isValidMove(startRow, startCol, endRow, endCol, board) ||
       queen_as_bishop.isValidMove(startRow, startCol, endRow, endCol, board)){
        return true;
    }
    return false;
}

/**
 * Determines if the queen is threatening the enemy king's position.
 * A queen threatens the king if the king is in the same row, column, or diagonal as the queen.
 *
 * This function uses the logic of both the rook and the bishop to determine the threat.
 *
 * @param myRow The current row of the queen.
 * @param myCol The current column of the queen.
 * @param EnemyKingRow The row position of the enemy king.
 * @param EnemyKingCol The column position of the enemy king.
 * @return True if the queen is threatening the enemy king, false otherwise.
 */
bool Queen::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    Rook queen_as_rook(myRow, myCol, this->getColor());
    Bishop queen_as_bishop(myRow, myCol, this->getColor());

    if(queen_as_rook.isThreat(myRow, myCol, EnemyKingRow, EnemyKingCol) ||
       queen_as_bishop.isThreat(myRow, myCol, EnemyKingRow, EnemyKingCol)){
        return true;
    }
    return false;
}
