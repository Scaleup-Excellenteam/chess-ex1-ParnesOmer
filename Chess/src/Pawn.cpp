//
// Created by omer on 4/14/2025.
//

#include "Pawn.h"

/**
 * Constructor for the Pawn class.
 * Initializes a pawn at the given position with the specified color.
 *
 * @param i The row position of the pawn.
 * @param j The column position of the pawn.
 * @param color The color of the pawn (WHITE or BLACK).
 */
Pawn::Pawn(int i, int j, PieceColor color) : Piece(i, j, color, PAWN){}


bool Pawn::isValidMove(int startRow, int startCol, int endRow, int endCol, const Board &board) const {
    // Direction of movement (forward for white or backward for black)
    PieceColor myColor = this->getColor();
    int direction = (myColor == WHITE) ? 1 : -1;

    // Normal forward movement
    if (endRow == startRow + direction && startCol == endCol) {
        if ((board.getPiece(endRow, endCol) == nullptr)) {
            return true; // Free square
        }
    }

    // Initial movement two squares forward
    if(isFirstMove(myColor, startRow) &&
       (endRow == startRow + (2 * direction)) && (startCol == endCol) ) {
        if (board.getPiece(startRow + direction, startCol) == nullptr &&
            board.getPiece(endRow, endCol) == nullptr) {
            return true; // Both squares are free
        }
    }

    // Eating diagonally
    if (endRow == startRow + direction && std::abs(endCol - startCol) == 1) {
        const Piece* targetPiece = board.getPiece(endRow, endCol);
        if (targetPiece != nullptr && targetPiece->getColor() != this->getColor()) {
            return true; // Opponent's piece diagonally
        }
    }

    // If we did not meet any conditions, the move is illegal
    return false;
}


bool Pawn::isThreat(int myRow, int myCol, int EnemyKingRow, int EnemyKingCol) const {
    // Direction of movement (forward for white or backward for black)
    int direction = (this->getColor() == WHITE) ? 1 : -1;
    // Eating diagonally
    if (EnemyKingRow == myRow + direction && std::abs(EnemyKingCol - myCol) == 1) {
        return true; // Opponent's piece diagonally
    }
    return false;
}


bool Pawn::isFirstMove(PieceColor color, int row) {
    if(color == WHITE){
        return row == 1;
    }
    return row == 6;
}


int Pawn::getValue() const {
    return Constants::PAWN_VALUE;
}


Piece *Pawn::clone() const {
    return new Pawn(*this);
}
