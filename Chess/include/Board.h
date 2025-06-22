//
// Created by omer on 4/3/2025.
//

#ifndef CHESS_EX1_PARNESOMER_MAIN_BOARD_H
#define CHESS_EX1_PARNESOMER_MAIN_BOARD_H
#include "Piece.h"
#include "Move.h"
#include "EvaluateAllMoves.h"
#include "Exception.h"
#include "Constants.h"
#include <string>
#include <sstream>
#include <vector>

class Piece;
class KingEnemies;

/**
 * Represents the chessboard and manages the state of the game.
 * This class handles the placement of pieces, turn management,
 * and validation of moves according to chess rules.
 */
class Board {
public:
    Board();
    ~Board();
    Board(const Board& other);              ///< Using copyHelper to copy the board state.
    Board& operator=(const Board& other);   ///< Using copyHelper to copy the board state.

    /// Validates if a move is legal. and return the move status.
    int isValidMove(int startRow, int startCol , int endRow, int endCol);
    /// Parses and applies a move from string input. returns the move status, makes the move if valid.
    int movePiece(const string& moveInput);
    /// Moves a piece from one position to another on the board
    void makeMove(Piece* source, int startRow, int startCol , int endRow, int endCol);
    /// Undoes a move by restoring the piece to its original position and updating the board.
    void undoMove(Piece* source, Piece* target, int startRow, int startCol, int endRow, int endCol);
    /// Handles pawn promotion when a pawn reaches the last row.
    int HandlePromotion(Piece *source, int newRow, int newCol); // only implement the promotion part without the representation on the board

    // getters and setters
    /// Returns a constant pointer to the piece at the given position, or nullptr if the square is empty.
    const Piece* getPiece(int row, int col) const;
    /// Returns the piece at a specific position on the board with permission to modify it.
    Piece* getPieceWithePermission(int row, int col);
    /// Access pieces in a row.
    std::vector<Piece*>& operator[](int row);

    // Evaluation of the best move
    /// Returns the top three recommended moves as strings.
    std::vector<std::string> getTopMoves(int numThreads, int depth);

    /// Switch the turn (white <-> black).
    void changeTurn() { isWhite = !isWhite; }
    /// Returns true if it's white's turn, false otherwise.
    bool getTurn() const { return isWhite; }
    /// Returns the current position of the white king.
    std::pair<int, int> getWhiteKingPosition() const { return whiteKingPosition; }
    /// Returns the current position of the black king.
    std::pair<int, int> getBlackKingPosition() const { return blackKingPosition; }
    /// Sets the position of the white king.
    void setWhiteKingPosition(int row, int col) { whiteKingPosition = {row, col}; }
    /// Sets the position of the black king.
    void setBlackKingPosition(int row, int col) { blackKingPosition = {row, col}; }

    /// Checks if the current king is in check.
    bool King_in_check(bool color) const;
    bool whiteKingCanCastle(bool RightCastle) const;
    bool blackKingCanCastle(bool RightCastle) const;

private:

    bool isWhite;                             /// Tracks which player's turn it is (true = white, false = black).
    int whiteKingMoved = 0;                   /// Indicates if the white king has moved.
    int blackKingMoved = 0;                   /// Indicates if the black king has moved.
    std::pair<int, int> WhiteRookStatus;      /// Indicates if the black rook has moved. (right, left).
    std::pair<int, int> BlackRookStatus;      /// Indicates if the white rook has moved. (right, left).
    std::vector<vector<Piece*>> board;        /// 2D vector representing the chessboard with pieces.
    KingEnemies* threats_to_white_king;       /// Tracks threats on the white king.
    KingEnemies* threats_to_black_king;       /// Tracks threats on the black king.

    std::pair<int, int> whiteKingPosition;    /// The starting position of the king
    std::pair<int, int> blackKingPosition;    /// The starting position of the king

    /// Initializes the board with pieces in their starting positions.
    void initializeBoard();
    /// Checks if a move puts the rival king in check.
    bool IsRivalKingInCheck(const Piece *sourcePiece, int startRow, int startCol , int endRow, int endCol);
    void copyHelper(const Board& other);
};

#endif //CHESS_EX1_PARNESOMER_MAIN_BOARD_H
