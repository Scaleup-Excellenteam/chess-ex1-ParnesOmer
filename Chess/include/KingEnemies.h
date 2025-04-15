//
// Created by omer on 4/14/2025.
//

#ifndef CHESS_KINGENEMIES_H
#define CHESS_KINGENEMIES_H
#include "Piece.h"
#include <vector>
#include <algorithm>
using namespace std;

class Piece;
class Board;

class KingEnemies {
    vector<Piece*> threat_from_pawn;
    vector<Piece*> threat_from_queen;
    vector<Piece*> threat_from_knight;
    vector<Piece*> threat_from_bishop;
    vector<Piece*> threat_from_rook;
    int KingX;
    int KingY;
public:
    KingEnemies(int x, int y);
    ~KingEnemies() = default;

    void updateThreats(const Board& board);
    bool isKingInCheck(const Board& board) const;
    void kingMoved(int x, int y, const Board& board);
    void updateThreatsOnMove(const Piece* movedPiece, int oldX, int oldY, int newX, int newY, const Board& board);

};


#endif //CHESS_KINGENEMIES_H
