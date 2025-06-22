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


/**
 * @brief
* Class for move score evaluation by given depth and scoring in chess.
* Uses multi-threading and minmax algorithm with alpha-beta pruning.
*/
class EvaluateAllMoves {

public:
    EvaluateAllMoves(int depth, const Board& board);
    ~EvaluateAllMoves();

    /// Disable copy constructor and assignment operator
    EvaluateAllMoves(const EvaluateAllMoves&) = delete;
    EvaluateAllMoves& operator=(const EvaluateAllMoves&) = delete;


    ///Evaluates scores for all legal moves in parallel and returns a priority queue of moves.
    MyPriorityQueue<std::unique_ptr<Move>> evaluateAllMoves(int numThreads);
    /// The function returns a vector of all legal moves for the current player.
    std::vector<std::unique_ptr<Move>> getAllValidMoves();

    /// Sort moves for better alpha-beta pruning
    void sortMovesByPriority(vector<std::unique_ptr<Move>>& moves);
    /// Give priority scores for move ordering
    int getMoveOrderingScore(Move* move);

    /// Minimax evaluation for one move
    int minimaxEvaluateMove(Move* move, int depth = 3, int alpha = INT_MIN, int beta = INT_MAX);

private:
    int depth;            /// Search depth
    const Board& board;   /// Reference to original board
    Board* tempBoard;     /// Board copy for simulations

    /// Evaluates the board position after a move, returning a score based on material and positional factors.
    int evaluateBoardPosition(Move* move, Piece *target, Piece *source);
    /// Get bonus for a piece at a specific position
    int getPositionalBonus(Piece* piece, int row, int col, bool isEndgame);
    /// Get bonus for king safety based on current and enemy moves
    int getKingSafetyBonus(const vector<std::unique_ptr<Move>>& currentPlayerMoves,
                           const vector<std::unique_ptr<Move>>& enemyPlayerMoves);
};

#endif //CHESS_EVALUATEALLMOVES_H
