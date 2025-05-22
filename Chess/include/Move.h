//
// Created by omer on 5/10/2025.
//

#ifndef CHESS_MOVESCORER_H
#define CHESS_MOVESCORER_H

#include "MyPriorityQueue.h"
using namespace std;

class MoveScorer {
    int score; // The score of the move

    int startPosition[2]; // The starting position of the piece
    int endPosition[2]; // The ending position of the piece
    int moveStatus; // The result of the isValidMove function - represents the status of the move

public:
    MoveScorer(int startRow, int startCol, int endRow, int endCol, int moveStatus);
    ~MoveScorer() = default;

    bool operator<(const MoveScorer& other) const;
};


#endif //CHESS_MOVESCORER_H
