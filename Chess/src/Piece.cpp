//
// Created by omer on 4/5/2025.
//

#include "../include/Piece.h"

Piece::Piece(int startX, int startY, PieceColor color) : currentX(startX), currentY(startY), color(color) {}

PieceColor Piece::getColor() const {
    return color;
}

PieceType Piece::getType() const {
    return type;
}

int Piece::getX() const {
    return currentX;
}

int Piece::getY() const {
    return currentY;
}

void Piece::setNewCell(int x, int y) {
    currentX = x;
    currentY = y;
}

bool Piece::isPromotion(int x) const {
    return false; // Default - not all tools are advanced
}

