//
// Created by omer on 4/3/2025.
//

#ifndef CHESS_EX1_PARNESOMER_MAIN_BOARD_H
#define CHESS_EX1_PARNESOMER_MAIN_BOARD_H
#include "Piece.h"
#include "Move.h"
#include "EvaluateAllMoves.h"
#include "Exception.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Piece;
class KingEnemies;

/**
 * Represents the chessboard and manages the state of the game.
 * This class handles the placement of pieces, turn management,
 * and validation of moves according to chess rules.
 */
class Board {
    bool isWhite;                         ///< Tracks which player's turn it is (true = white, false = black).
    vector<vector<Piece*>> board;         ///< 2D vector representing the chessboard with pieces.
    KingEnemies* threats_to_white_king;   ///< Tracks threats on the white king.
    KingEnemies* threats_to_black_king;   ///< Tracks threats on the black king.

    pair<int, int> whiteKingPosition;     ///< The starting position of the king
    pair<int, int> blackKingPosition;     ///< The starting position of the king

    /// Helper to copy board state from another Board.
    void copyHelper(const Board& other);
    /// Initializes the chessboard with starting positions.
    void initializeBoard();
    /// Checks if a move puts the rival king in check.
    bool IsRivalKingInCheck(const Piece *sourcePiece, int startRow, int startCol , int endRow, int endCol);
    /// Checks if the current king is in check.
    bool King_in_check(bool f);
public:
    /// Constructor.
    Board();
    /// Destructor.
    ~Board();
    /// Copy constructor.
    Board(const Board& other);
    /// Assignment operator.
    Board& operator=(const Board& other);

    // Implementation of the move
    /// Validates if a move is legal. and return the move status.
    int isValidMove(int startRow, int startCol , int endRow, int endCol);
    /// Parses and applies a move from string input. returns the move status, makes the move if valid.
    int movePiece(const string& moveInput);
    /// Moves a piece from one position to another on the board. and updates the king's threat tracking.
    void makeMove(Piece* source, int startRow, int startCol , int endRow, int endCol);
    /// Undoes a move by restoring the piece to its original position and updating the board.
    void undoMove(Piece* source, Piece* target, int startRow, int startCol, int endRow, int endCol);
    /// Handles pawn promotion when a pawn reaches the last row.
    bool HandlePromotion(Piece *source, int newRow, int newCol); // only implement the promotion part without the representation on the board

    // getters and setters
    /// Returns a const pointer to the piece at (row, col).
    const Piece* getPiece(int row, int col) const;
    /// Returns a pointer to the piece at (row, col) with write permission.
    Piece* getPieceWithePermission(int row, int col);
    /// Access pieces in a row.
    vector<Piece*>& operator[](int row);
    /// Switch the turn (white <-> black).
    void changeTurn() { isWhite = !isWhite; }
    /// Returns true if it's white's turn, false otherwise.
    bool getTurn() const { return isWhite; }
    /// Returns the current position of the white king.
    pair<int, int> getWhiteKingPosition() const { return whiteKingPosition; }
    /// Returns the current position of the black king.
    pair<int, int> getBlackKingPosition() const { return blackKingPosition; }
    /// Sets the position of the white king.
    void setWhiteKingPosition(int row, int col) { whiteKingPosition = {row, col}; }
    /// Sets the position of the black king.
    void setBlackKingPosition(int row, int col) { blackKingPosition = {row, col}; }

    // Evaluation of the best move
    /// Returns the top three recommended moves as strings.
    vector<string> getTopMoves();
};

#endif //CHESS_EX1_PARNESOMER_MAIN_BOARD_H
