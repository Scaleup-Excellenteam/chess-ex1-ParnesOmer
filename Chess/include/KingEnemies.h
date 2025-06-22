//
// Created by omer on 4/14/2025.
//

#ifndef CHESS_KINGENEMIES_H
#define CHESS_KINGENEMIES_H
#include "Piece.h"
#include <vector>
#include <algorithm>
#include <iostream>

class Piece;
class Board;

/**
 * The KingEnemies class is responsible for tracking and managing threats to the king.
 * It keeps track of the pieces that threaten the king, updates threats dynamically as the game progresses,
 * and determines if the king is in check.
 */
class KingEnemies {
public:
    explicit KingEnemies(bool isWhite);
    ~KingEnemies();
    KingEnemies(const KingEnemies& other);              ///< Using copyHelper to copy the board state.
    KingEnemies& operator=(const KingEnemies& other);   ///< Using copyHelper to copy the board state.

    /// Updates the threats to the king by analyzing the entire chessboard.
    void updateThreats(const Board& board);
    /// Checks if the king is in check.
    bool isKingInCheck(const Board& board) const;
    /// Updates threats after a piece has moved.
    void updateThreatsOnMove(const Piece* movedPiece, int oldRow, int oldCol, int newRow, int newCol, const Board& board);

private:

    bool isWhite;                                    ///< Indicates if the king is white or black
    std::vector<const Piece*> threat_from_pawn;      ///< List of pawns threatening the king
    std::vector<const Piece*> threat_from_queen;     ///< List of queens threatening the king
    std::vector<const Piece*> threat_from_knight;    ///< List of knights threatening the king
    std::vector<const Piece*> threat_from_bishop;    ///< List of bishops threatening the king
    std::vector<const Piece*> threat_from_rook;      ///< List of rooks threatening the king

    /// Returns the king's current position for this color.
    std::pair<int, int> getKingPosition(const Board& board) const;
    /// Checks if the path between two positions is clear.
    static bool isPathClear(int startRow, int startCol, int endRow, int endCol, const Board& board);
    void copyHelper(const KingEnemies& other);
};

#endif //CHESS_KINGENEMIES_H
