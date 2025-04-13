//
// Created by omer on 4/5/2025.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include "Board.h"
enum PieceColor { WHITE = 1, BLACK = 0};
using namespace std;
class Board;

class Piece {
    PieceColor color;
protected:
    int currentX;
    int currentY;
public:
    explicit Piece(int startX, int startY ,PieceColor color) : currentX(startX), currentY(startY), color(color) {}
    virtual ~Piece() {}

    PieceColor getColor() const { return color; }

    int getRow() {return currentX;}
    int getCol() {return currentY;}
    void setNewCell(int x, int y) {
        currentX = x;
        currentY = y;
    }

    virtual bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const = 0;

};


#endif //CHESS_PIECE_H
