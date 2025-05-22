//
// Created by omer on 5/13/2025.
//

#ifndef CHESS_EVALUATEALLMOVES_H
#define CHESS_EVALUATEALLMOVES_H
#include "Board.h"
#include "Move.h"
#include <vector>

class Board;
class Piece;

using namespace std;

/**
 * @brief Class for evaluating all possible chess moves from a given board state.
 *
 * Provides methods to generate, evaluate, and score all legal moves for the current player,
 * using a simple search tree up to a specified depth.
 * Assumes Board, Piece, and Move classes are defined elsewhere.
 */
class EvaluateAllMoves {
    int depth;            ///< The depth of the search tree for move evaluation.
    const Board& board;   ///< Reference to the original chessboard.
    Board* tempBoard;     ///< Temporary board used for move simulations.

    ///< Calculates the score of a move
    int getMoveScore(Move* move, Piece* target, Piece *source);
    ///< Calculates the net threat impact of a move
    int moveMakeOrInThreats(Move* move, Piece* movedPiece);
public:
    /**
     * @brief Constructor for EvaluateAllMoves. Initializes the evaluator for a given board and search depth.
     * @param depth The depth of the search tree for move evaluation.
     * @param board Reference to the original chessboard.
     */
    EvaluateAllMoves(int depth, const Board& board);
    /**
     * @brief Destructor for EvaluateAllMoves. Cleans up the temporary board.
     */
    ~EvaluateAllMoves();

    /**
     * @brief Generates all valid moves for the current player, evaluates their scores, and returns them.
     * @return Vector of pointers to Move, scored and ready for further processing.
     *
     * Note: The caller is responsible for freeing the returned Move pointers.
     */
    vector<Move*> evaluateAllMoves();
    /**
     * @brief Returns all valid (legal) moves for the current player from the current board position.
     * @return Vector of pointers to all valid Move objects.
     *
     * Note: The caller is responsible for freeing the returned Move pointers.
     */
    vector<Move*> getAllValidMoves();
    /**
     * @brief Recursively evaluates a single move to a given depth using a simple minimax approach.
     * @param move The move to evaluate.
     * @param depth The remaining search depth (default: 3).
     * @return The evaluated score for this move, taking into account possible opponent responses.
     */
    int evaluateOneMove(Move* move, int depth = 3);
};

#endif //CHESS_EVALUATEALLMOVES_H
