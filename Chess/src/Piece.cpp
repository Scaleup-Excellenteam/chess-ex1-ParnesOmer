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

/**
 * Gets the color of the piece.
 *
 * @return The color of the piece (white or black).
 */
PieceColor Piece::getColor() const {
    return color;
}

/**
 * Gets the type of the piece.
 *
 * @return The type of the piece (e.g., pawn, rook, etc.).
 */
PieceType Piece::getType() const {
    return type;
}

/**
 * Gets the current X-coordinate (row) of the piece.
 *
 * @return The current row of the piece on the board.
 */
int Piece::getX() const {
    return currentX;
}

/**
 * Gets the current Y-coordinate (column) of the piece.
 *
 * @return The current column of the piece on the board.
 */
int Piece::getY() const {
    return currentY;
}

/**
 * Updates the position of the piece to a new cell.
 *
 * @param x The new X-coordinate (row) of the piece.
 * @param y The new Y-coordinate (column) of the piece.
 */
void Piece::setNewCell(int x, int y) {
    currentX = x;
    currentY = y;
}

/**
 * Copy constructor for the Piece class.
 * Creates a new Piece instance by copying attributes from another Piece instance.
 *
 * @param other The Piece instance to copy from.
 */
Piece::Piece(const Piece &other) {
    this->type = other.type;
    this->currentX = other.currentX;
    this->currentY = other.currentY;
    this->color = other.color;
}

/**
 * Copy assignment operator for the Piece class.
 * Copies the attributes (type, position, and color) from another Piece instance.
 *
 * @param other The Piece instance to copy from.
 * @return A reference to the current Piece instance after assignment.
 */
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


