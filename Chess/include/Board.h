//
// Created by omer on 4/3/2025.
//

#ifndef CHESS_EX1_PARNESOMER_MAIN_BOARD_H
#define CHESS_EX1_PARNESOMER_MAIN_BOARD_H
#include "Piece.h"
#include <string>
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
    bool isWhite; // Tracks which player's turn it is (true = white, false = black).
    vector<vector<Piece*>> board; // 2D vector representing the chessboard with pieces.
    KingEnemies* threats_to_white_king; // Tracks threats on the white king.
    KingEnemies* threats_to_black_king; // Tracks threats on the black king.
    void initializeBoard();
    bool IsMyKingInCheck(const Piece *sourcePiece, int endRow, int endCol);
    bool IsRivalKingInCheck(const Piece *sourcePiece, int startRow, int startCol , int endRow, int endCol);
    bool King_in_check(bool f);
public:
    Board();
    ~Board();
    /**
     * Copy constructor is deleted to prevent copying.
     */
    Board(const Board&) = delete;
    /**
     * Copy assignment operator is deleted to prevent copying.
     */
    Board& operator=(const Board&) = delete;

    const Piece* getPiece(int row, int col) const;
    int isValidMove(int startRow, int startCol , int endRow, int endCol);

    int movePiece(const string& moveInput);
};


#endif //CHESS_EX1_PARNESOMER_MAIN_BOARD_H
