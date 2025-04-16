//
// Created by omer on 4/5/2025.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "Board.h"
#include "KingEnemies.h"
#include <vector>
using namespace std;

class Board;
class KingEnemies;

// Enum representing the color of a chess piece.
enum PieceColor { WHITE = 1, BLACK = 0};

// Enum representing the type of chess piece.
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };


/**
 * Abstract base class representing a generic chess piece.
 * This class provides common functionality for all chess pieces and defines pure virtual methods
 * for determining valid moves and threats to the king.
 */
class Piece {
    PieceColor color;
protected:
    PieceType type;
    int currentX;
    int currentY;
public:
    explicit Piece(int startRow, int startCol , PieceColor color, PieceType type);
    virtual ~Piece() = default;

    Piece(const Piece& other);
    Piece& operator=(const Piece& other);

    PieceColor getColor() const;
    PieceType getType() const;
    int getX() const;
    int getY() const;
    void setNewCell(int x, int y);

    virtual bool isValidMove(int startRow, int startCol, int endRow, int endCol, const Board& board) const = 0;
    virtual bool isThreat(int myRow, int myCol, int KingRow, int KingCol) const = 0;
};



#endif //CHESS_PIECE_H
