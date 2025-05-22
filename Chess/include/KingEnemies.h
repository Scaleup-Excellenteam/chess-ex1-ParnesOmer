//
// Created by omer on 4/14/2025.
//

#ifndef CHESS_KINGENEMIES_H
#define CHESS_KINGENEMIES_H
#include "Piece.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Piece;
class Board;

/**
 * The KingEnemies class is responsible for tracking and managing threats to the king.
 * It keeps track of the pieces that threaten the king, updates threats dynamically as the game progresses,
 * and determines if the king is in check.
 */
class KingEnemies {
    bool isWhite; ///< Indicates if the king is white or black
    vector<const Piece*> threat_from_pawn;   ///< List of pawns threatening the king
    vector<const Piece*> threat_from_queen;  ///< List of queens threatening the king
    vector<const Piece*> threat_from_knight; ///< List of knights threatening the king
    vector<const Piece*> threat_from_bishop; ///< List of bishops threatening the king
    vector<const Piece*> threat_from_rook;   ///< List of rooks threatening the king

    /// Copies threat data from another KingEnemies object.
    void copyHelper(const KingEnemies& other);

    /// Returns the king's current position for this color.
    pair<int, int> getKingPosition(const Board& board) const;
    /// Checks if the path between two positions is clear.
    static bool isPathClear(int startRow, int startCol, int endRow, int endCol, const Board& board);
public:
    /// Constructor.
    KingEnemies(bool isWhite);
    /// Destructor.
    ~KingEnemies();
    /// Copy constructor.
    KingEnemies(const KingEnemies& other);
    /// Copy assignment operator.
    KingEnemies& operator=(const KingEnemies& other);

    /// Updates the lists of threats based on the current board.
    void updateThreats(const Board& board);
    /// Checks if the king is in check.
    bool isKingInCheck(const Board& board) const;
    /// Updates threats after a piece has moved.
    void updateThreatsOnMove(const Piece* movedPiece, int oldRow, int oldCol, int newRow, int newCol, const Board& board);
};

#endif //CHESS_KINGENEMIES_H
