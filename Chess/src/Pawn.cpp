//
// Created by omer on 4/14/2025.
//

#include "Pawn.h"

Pawn::Pawn(int i, int j, PieceColor color) : Piece(i, j, color), hasMoved(false){
     type = PAWN;
}

bool Pawn::isValidMove(int startX, int startY, int endX, int endY, const Board &board) const {
    // Direction of movement (forward for white or backward for black)
    int direction = (this->getColor() == WHITE) ? 1 : -1;

    // Normal forward movement
    if (endX == startX + direction && startY == endY) {
        if ((board.getPiece(endX, endY) == nullptr)) {
            //setHasMoved();
            return true; // Free square
        }
    }

    // Initial movement two squares forward
    if (!hasMoved && endX == startX + (2 * direction) && startY == endY) {
        if (board.getPiece(startX + direction, startY) == nullptr &&
            board.getPiece(endX, endY) == nullptr) {
            //setHasMoved();
            return true; // Both squares are free
        }
    }

    // Eating diagonally
    if (endX == startX + direction && abs(endY - startY) == 1) {
        const Piece* targetPiece = board.getPiece(endX, endY);
        if (targetPiece != nullptr && targetPiece->getColor() != this->getColor()) {
            //setHasMoved();
            return true; // Opponent's piece diagonally
        }
    }

    // If we did not meet any conditions, the move is illegal
    return false;
}

// Check if the soldier has reached the last line (Promotion)
bool Pawn::isPromotion(int x) const {
    return (this->getColor() == WHITE && x == 7) || (this->getColor() == BLACK && x == 0);
}

// Update the soldier's status
void Pawn::setHasMoved() {
    hasMoved = true;
}

bool Pawn::isThreat(int myX, int myY, int EnemyKingX, int EnemyKingY) const {
    // Direction of movement (forward for white or backward for black)
    int direction = (this->getColor() == WHITE) ? 1 : -1;
    // Eating diagonally
    if (EnemyKingX == myX + direction && abs(EnemyKingY - myY) == 1) {
        return true; // Opponent's piece diagonally
    }
    return false;
}
