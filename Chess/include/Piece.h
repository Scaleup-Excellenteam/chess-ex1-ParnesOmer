//
// Created by omer on 4/5/2025.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "Board.h"
#include "KingEnemies.h"
#include <vector>

class Board;
class KingEnemies;

/// Enum representing the color of a chess piece.
enum PieceColor { WHITE = 1, BLACK = 0};

/// Enum representing the type of chess piece.
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };


/**
 * Abstract base class representing a generic chess piece.
 * This class provides common functionality for all chess pieces and defines pure virtual methods
 * for determining valid moves and threats to the king.
 */
class Piece {
public:
    explicit Piece(int startRow, int startCol , PieceColor color, PieceType type);
    virtual ~Piece() = default;

    Piece(const Piece& other);
    Piece& operator=(const Piece& other);

    PieceColor getColor() const;
    PieceType getType() const;
    int getX() const;
    int getY() const;
    void setNewCell(int x, int y);       /// Updates the position of the piece to a new cell.

    virtual Piece* clone() const = 0;    /// Pure virtual method for cloning the piece.
    virtual int getValue() const = 0;
    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const = 0;
    virtual bool isThreat(int myRow, int myCol, int KingRow, int KingCol) const = 0;

protected:
    PieceType type;     /// Type of the piece.
    int currentX;       /// Current X(row) of the piece on the board.
    int currentY;       /// Current Y(column) of the piece on the board.

private:
    PieceColor color;   /// Color of the piece.
};

#endif //CHESS_PIECE_H