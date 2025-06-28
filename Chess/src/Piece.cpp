//
// Created by omer on 4/5/2025.
//

#include "../include/Piece.h"

/**
 * Constructor for the Piece class.
 * Initializes the piece with its starting position, color, and type.
 *
 * @param startRow The initial row of the piece.
 * @param startCol The initial column of the piece.
 * @param color The color of the piece (white or black).
 * @param type The type of the piece (e.g., pawn, rook, etc.).
 */
Piece::Piece(int startRow, int startCol, PieceColor color, PieceType type) : currentX(startRow), currentY(startCol), color(color), type(type){}


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


Piece::Piece(const Piece& other) {
    this->type = other.type;
    this->currentX = other.currentX;
    this->currentY = other.currentY;
    this->color = other.color;
}


Piece &Piece::operator=(const Piece &other) {
    // Check for self-assignment before proceeding with the copy.
    if(this != &other){
        this->type = other.type;
        this->currentX = other.currentX;
        this->currentY = other.currentY;
        this->color = other.color;
    }
    return *this;
}
