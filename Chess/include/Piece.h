//
// Created by omer on 4/5/2025.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "Board.h"
#include "KingEnemies.h"
#include <vector>
enum PieceColor { WHITE = 1, BLACK = 0};
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

using namespace std;
class Board;
class KingEnemies;

class Piece {
    PieceColor color;
protected:
    PieceType type;
    int currentX;
    int currentY;

public:
    explicit Piece(int startX, int startY ,PieceColor color);
    virtual ~Piece() = default;

    Piece(const Piece& other){
        this->type = other.type;
        this->currentX = other.currentX;
        this->currentY = other.currentY;
        this->color = other.color;
    }
    Piece& operator=(const Piece& other){
        if(this != &other){
            this->type = other.type;
            this->currentX = other.currentX;
            this->currentY = other.currentY;
            this->color = other.color;
        }
        return *this;
    }

    PieceColor getColor() const;
    PieceType getType() const;
    int getX() const;
    int getY() const;
    void setNewCell(int x, int y);

    virtual bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const = 0;
    virtual bool isThreat(int myX, int myY, int KingX, int KingY) const = 0;
    virtual bool isPromotion(int x) const;
    virtual void setHasMoved() const {}
};



#endif //CHESS_PIECE_H
