//
// Created by omer on 5/10/2025.
//

#include "Move.h"

Move::Move(int startRow, int startCol, int endRow, int endCol, int moveStatus) : score(0), moveStatus(moveStatus),
             startPosition(make_pair(startRow, startCol)), endPosition(make_pair(endRow, endCol)) {}

void Move::setScore(int newScore)  { score = newScore; }

int Move::getScore() const { return score; }

int Move::getMoveStatus() const { return moveStatus; }

pair<int, int> Move::getStartPosition() { return startPosition;}

pair<int, int> Move::getEndPosition() { return endPosition; }

bool Move::operator<(const Move& other) const { return score < other.score; }

ostream& operator<<(ostream& os, const Move& move) {
    os << static_cast<char>(move.startPosition.first + 'a') << move.startPosition.second + 1
       << static_cast<char>(move.endPosition.first + 'a') << move.endPosition.second + 1; //<< " with score: " << move.score
    return os;
}
