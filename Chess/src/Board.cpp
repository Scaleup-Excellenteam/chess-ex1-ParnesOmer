//
// Created by omer on 4/3/2025.
//

#include "../include/Board.h"
#include <stdexcept>
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "KingEnemies.h"

/**
 * Constructor for the Board class.
 * Initializes the chessboard with pieces in their starting positions and sets up king threat tracking.
 */
Board::Board() : isWhite(true){
    board.resize(8, vector<Piece*>(8, nullptr));
    threats_to_white_king = new KingEnemies(0, 4);
    threats_to_black_king = new KingEnemies(7, 4);
    initializeBoard();
}

/**
 * Destructor for the Board class.
 * Frees memory allocated for the chessboard and threat tracking objects.
 */
Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
    delete threats_to_white_king;
    delete threats_to_black_king;
}

/**
 * Initializes the board with pieces in their starting positions.
 */
void Board::initializeBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece *piece = nullptr;
            if (i == 0 || i == 7) {
                // First or last line
                PieceColor color = (i == 0) ? WHITE : BLACK;
                if (j == 0 || j == 7) { piece = new Rook(i, j, color); }
                else if (j == 1 || j == 6) { piece = new Knight(i, j, color); }
                else if (j == 2 || j == 5) { piece = new Bishop(i, j, color); }
                else if (j == 3) { piece = new Queen(i, j, color); }
                else if (j == 4) piece = new King(i, j, color);
            } else if (i == 1 || i == 6) {
                // Second or penultimate line
                PieceColor color = (i == 1) ? WHITE : BLACK;
                piece = new Pawn(i, j, color);
            }
            board[i][j] = piece;
        }
    }
}

/**
 * Retrieves the piece at a specific position on the board.
 *
 * @param row The row index.
 * @param col The column index.
 * @return A constant pointer to the piece at the given position, or nullptr if the square is empty.
 */
const Piece *Board::getPiece(int row, int col) const {
    return board[row][col];
}

/**
 * Validates a move based on chess rules and updates the board state if the move is valid.
 *
 * @param startRow The starting row of the piece.
 * @param startCol The starting column of the piece.
 * @param endRow The target row of the piece.
 * @param endCol The target column of the piece.
 * @return An integer code representing the result of the move (e.g., success, invalid move, check).
 */
int Board::isValidMove(int startRow, int startCol , int endRow, int endCol) {
    Piece* source = board[startRow][startCol];
    Piece* target = board[endRow][endCol];

    // The source square is empty
    if(source == nullptr){
        return 11;
    }

    PieceColor sourceColor = source->getColor();

    // The piece in the source square belongs to the opposing player
    if(sourceColor != isWhite){
        return 12;
    }

    // The target square contains a piece of the same player
    if(target != nullptr && sourceColor == target->getColor()) {
        return 13;
    }

    // Check if the move complies with the piece's movement rules
    if(!source->isValidMove(startRow, startCol, endRow, endCol, *this)){
        return 21;
    }

    // Simulate the move
    source->setNewCell(endRow, endCol);
    board[endRow][endCol] = source;
    board[startRow][startCol] = nullptr;

    // Check if the move leaves the player's king in check
    if(IsMyKingInCheck(source, endRow, endCol)){
        // Reversal simulated move
        source->setNewCell(startRow, startCol);
        board[startRow][startCol] = source;
        board[endRow][endCol] = target;

        if(source->getType() == KING){
            // Updates the threat balance according to the king's old location
            if (isWhite) {
                threats_to_white_king->kingMoved(startRow, startCol, *this);
            } else {
                threats_to_black_king->kingMoved(startRow, startCol, *this);
            }
        }
        return 31;
    }

    // Handle pawn promotion
    if(source->getType() == PAWN) {
        // Check if the soldier has reached the last line (Promotion)
        if ((sourceColor == WHITE && endRow == 7) || (sourceColor == BLACK && endRow == 0)) {
            // If he does ,it becomes a queen.
            delete board[endRow][endCol];
            board[endRow][endCol] = new Queen(endRow, endCol, sourceColor);
        }
    }

    // No need to reverse the simulated move from this point
    // Check if the move puts the rival's king in check
    if(IsRivalKingInCheck(source, startRow, startCol, endRow, endCol)){
        // Switch turns for the next move
        isWhite = !isWhite;
        return 41;
    }

    // Switch turns for the next move
    isWhite = !isWhite;
    return 42;
}

/**
 * Checks if the player's king is in check after a move.
 *
 * @param sourcePiece The piece being moved.
 * @param endRow The row position after the move.
 * @param endCol The column position after the move.
 * @return True if the king is in check, false otherwise.
 */
bool Board::IsMyKingInCheck(const Piece *sourcePiece, int endRow, int endCol) {
    if(sourcePiece->getType() == KING){
        // Updates the threat balance according to the king's new location
        if (isWhite) {
            threats_to_white_king->kingMoved(endRow, endCol, *this);
        } else {
            threats_to_black_king->kingMoved(endRow, endCol, *this);
        }
    }

    //There is check
    return King_in_check(isWhite);
}

/**
 * Checks if the rival's king is in check after a move.
 *
 * @param sourcePiece The piece being moved.
 * @param startRow The starting row of the piece.
 * @param startCol The starting column of the piece.
 * @param endRow The row position after the move.
 * @param endCol The column position after the move.
 * @return True if the rival's king is in check, false otherwise.
 */
bool Board::IsRivalKingInCheck(const Piece *sourcePiece, int startRow, int startCol , int endRow, int endCol) {
    // Checks whether the move added a threat to the enemy's king
    if(isWhite){
        threats_to_black_king->updateThreatsOnMove(sourcePiece, startRow, startCol, endRow, endCol, *this);
    }else{
        threats_to_white_king->updateThreatsOnMove(sourcePiece, startRow, startCol, endRow, endCol, *this);
    }

    return King_in_check(!isWhite);
}

/**
 * Determines if a specific king is in check.
 *
 * @param whichKing True for white king, false for black king.
 * @return True if the specified king is in check, false otherwise.
 */
bool Board::King_in_check(bool whichKing) {
    if (whichKing) {
        return threats_to_white_king->isKingInCheck(*this);
    } else {
        return threats_to_black_king->isKingInCheck(*this);
    }
}

/**
 * Converts a move string (e.g., "e2e4") into board coordinates and attempts to perform the move.
 *
 * @param moveInput The string representing the move.
 * @return An integer code representing the result of the move.
 * @throws invalid_argument If the move string is invalid.
 */
int Board::movePiece(const string& moveInput) {
    int startRow = tolower(moveInput[0]) - 'a';
    int startCol = moveInput[1] - '1';
    int endRow = tolower(moveInput[2]) - 'a';
    int endCol = moveInput[3] - '1';

    if (startRow < 0 || startRow > 7 || startCol < 0 || startCol > 7 ||
        endRow < 0 || endRow > 7 || endCol < 0 || endCol > 7) {
        throw invalid_argument("Invalid move string");
    }

    //Call isValidMove to get the writing code.
    // and if the code Represents a legal move, the function also changes the player's turn
    return isValidMove(startRow, startCol, endRow, endCol);
}