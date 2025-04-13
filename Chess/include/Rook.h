//
// Created by omer on 4/3/2025.
//

#ifndef CHESS_EX1_PARNESOMER_MAIN_ROOK_H
#define CHESS_EX1_PARNESOMER_MAIN_ROOK_H
#include "Piece.h"


class Rook : public Piece{
public:
    Rook(int i, int j, PieceColor color) : Piece(i, j, color) {}
    ~Rook() = default;

    bool isValidMove(int startX, int startY, int endX, int endY, const Board& board) const override{
        // Check if the path is free
        if (startX == endX) {
            // Move along a column
            int step = (startY < endY) ? 1 : -1; // Direction of movement
            for (int y = startY + step; y != endY; y += step) {
                if (board.getPiece(startX, y) != nullptr) {
                    return false; // There is a tool on the way
                }
            }
        } else if (startY == endY) {
            // Move along row
            int step = (startX < endX) ? 1 : -1; // Direction of movement
            for (int x = startX + step; x != endX; x += step) {
                if (board.getPiece(x, startY) != nullptr) {
                    return false; // There is a tool on the way
                }
            }
        }else {
            // Check if the move is in the same row or column
            return false;
        }

        // If we passed the tests, the move is legal
        return true;
    }

};

#endif //CHESS_EX1_PARNESOMER_MAIN_ROOK_H
