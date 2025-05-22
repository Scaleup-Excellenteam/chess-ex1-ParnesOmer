//
// Created by omer on 5/10/2025.
//

#include "MoveScorer.h"

MoveScorer::MoveScorer(int startRow, int startCol, int endRow, int endCol, int moveStatus) : score(0), moveStatus(moveStatus) {
    // Initialize the start and end positions
    startPosition[0] = startRow;
    startPosition[1] = startCol;
    endPosition[0] = endRow;
    endPosition[1] = endCol;
}

bool MoveScorer::operator<(const MoveScorer &other) const {
    return score < other.score;
}


