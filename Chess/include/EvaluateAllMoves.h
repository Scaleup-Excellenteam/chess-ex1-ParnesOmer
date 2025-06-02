//
// Created by omer on 5/13/2025.
//

#ifndef CHESS_EVALUATEALLMOVES_H
#define CHESS_EVALUATEALLMOVES_H
#include "Board.h"
#include "Move.h"
#include "ThreadsPool.h"
#include "ThreadSafePriorityQueue.h"
#include <vector>
#include <thread>
#include <atomic>

class Board;
class Piece;

using namespace std;

/**
 * @brief Evaluates and scores all legal moves for a given board state and search depth.
 */
class EvaluateAllMoves {
    int depth;            // Search depth
    const Board& board;   // Reference to original board
    Board* tempBoard;     // Board copy for simulations

    int getMoveScore(Move* move, Piece* target, Piece *source); // Score one move
    int moveMakeOrInThreats(Move* move, Piece* movedPiece);     // Net threats for a move
public:
    EvaluateAllMoves(int depth, const Board& board);
    ~EvaluateAllMoves();

    // Disable copy constructor and assignment operator
    EvaluateAllMoves(const EvaluateAllMoves&) = delete;
    EvaluateAllMoves& operator=(const EvaluateAllMoves&) = delete;

    MyPriorityQueue<std::unique_ptr<Move>> evaluateAllMoves(int numThreads); // Evaluate all moves in parallel
    std::vector<std::unique_ptr<Move>> getAllValidMoves();                   // Generate all legal moves
    int evaluateOneMove(Move* move, int depth = 3);                          // Minimax evaluation for one move
};

#endif //CHESS_EVALUATEALLMOVES_H
