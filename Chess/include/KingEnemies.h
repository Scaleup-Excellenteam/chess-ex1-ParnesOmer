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

/**
 * The KingEnemies class is responsible for tracking and managing threats to the king.
 * It keeps track of the pieces that threaten the king, updates threats dynamically as the game progresses,
 * and determines if the king is in check.
 */
class KingEnemies {
    vector<Piece*> threat_from_pawn;   ///< List of pawns threatening the king
    vector<Piece*> threat_from_queen;  ///< List of queens threatening the king
    vector<Piece*> threat_from_knight; ///< List of knights threatening the king
    vector<Piece*> threat_from_bishop; ///< List of bishops threatening the king
    vector<Piece*> threat_from_rook;   ///< List of rooks threatening the king
    int KingRow; ///< The current row of the king
    int KingCol; ///< The current column of the king

    static bool isPathClear(int startRow, int startCol, int endRow, int endCol, const Board& board);
public:
    KingEnemies(int row, int col);
    /**
     * Default destructor for the KingEnemies class.
     */
    ~KingEnemies() = default;

    void updateThreats(const Board& board);
    bool isKingInCheck(const Board& board) const;
    void kingMoved(int row, int col, const Board& board);
    void updateThreatsOnMove(const Piece* movedPiece, int oldRow, int oldCol, int newRow, int newCol, const Board& board);

};


#endif //CHESS_KINGENEMIES_H
