//
// Created by omer on 5/10/2025.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "MyPriorityQueue.h"
#include <iostream>

using namespace std;

/**
 * @brief Represents a chess move, including its score, start/end positions, and move status.
 *
 * The Move class is used for storing information about a single chess move, including
 * its evaluation score, the starting and ending positions, and an optional move status code.
 */
class Move {
    int score;                    ///< The score or evaluation assigned to this move.
    pair<int, int> startPosition; ///< The starting position (row, col) of the piece.
    pair<int, int> endPosition;   ///< The ending position (row, col) of the piece.
    int moveStatus;               ///< The status/result code of the move (e.g., 41 for check, 42 for normal).
public:
    /**
     * @brief Constructor for Move.
     * @param startRow The starting row of the piece.
     * @param startCol The starting column of the piece.
     * @param endRow The ending row of the piece.
     * @param endCol The ending column of the piece.
     * @param moveStatus The status/result code for this move.
     */
    Move(int startRow, int startCol, int endRow, int endCol, int moveStatus);
    /// Default destructor.
    ~Move() = default;

    // getters and setters
    /// Sets the score of the move.
    void setScore(int newScore);
    /// Gets the score of the move.
    int getScore() const;
    /// Gets the move status.
    int getMoveStatus() const;
    /// Gets the starting position of the move.
    pair<int, int> getStartPosition();
    /// Gets the ending position of the move.
    pair<int, int> getEndPosition();

    /// Compares two moves based on their score (for priority queues, etc).
    bool operator<(const Move& other) const;
    /// Output stream operator for printing a move.
    friend ostream& operator<<(ostream& os, const Move& move);
};

#endif //CHESS_MOVE_H
