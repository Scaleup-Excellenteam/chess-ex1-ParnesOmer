//
// Created by omer on 4/3/2025.
//

#include "../include/Board.h"
#include <stdexcept>
#include <iostream>
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
    // Initialize the king positions
    whiteKingPosition = {0, 4}; // Initial position of the white king
    blackKingPosition = {7, 4}; // Initial position of the black king
    // Initialize the threats to the kings
    threats_to_white_king = new KingEnemies(true);
    threats_to_black_king = new KingEnemies(false);
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
const Piece* Board::getPiece(int row, int col) const {
    if(row < 0 || row >= 8 || col < 0 || col >= 8) {
        throw BoardOutOfRange();
    }
    return board[row][col];
}

/**
 * Retrieves the piece at a specific position on the board with permission to modify it.
 *
 * @param row The row index.
 * @param col The column index.
 * @return A pointer to the piece at the given position, or nullptr if the square is empty.
 */
Piece* Board::getPieceWithePermission(int row, int col) {
    if(row < 0 || row >= 8 || col < 0 || col >= 8) {
        throw BoardOutOfRange();
    }
    return board[row][col];
}

/**
 * Overloaded subscript operator to access pieces on the board.
 *
 * @param row The row index.
 * @return A reference to the vector of pieces in the specified row.
 */
vector<Piece *> &Board::operator[](int row) {
    if(row < 0 || row >= 8) {
        throw BoardOutOfRange();
    }
    return board[row];
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
    makeMove(source, startRow, startCol, endRow, endCol);

    // Check if the move leaves the player's king in check
    if(King_in_check(isWhite)){
        // Reversal simulated move
        undoMove(source, target, startRow, startCol, endRow, endCol);
        return 31;
    }

    // Check if the move puts the rival's king in check
    if(IsRivalKingInCheck(source, startRow, startCol, endRow, endCol)){
        // Reversal simulated move
        undoMove(source, target, startRow, startCol, endRow, endCol);
        return 41;
    }

    // Reversal simulated move
    undoMove(source, target, startRow, startCol, endRow, endCol);
    return 42;
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
    // Saving the pieces in the start and end positions
    Piece* source = board[startRow][startCol];

    //Call isValidMove to get the writing code.
    int codeResponse = isValidMove(startRow, startCol, endRow, endCol);
    if (codeResponse > 40) {  // If the move was successful
        makeMove(source, startRow, startCol, endRow, endCol);
        if(codeResponse == 42 && source->getType() == PAWN) {
            if(HandlePromotion(source, endRow, endCol)){ // Handle pawn promotion. If returns true, the rival's king is in check
                codeResponse = 41;
            }
        }
        isWhite = !isWhite; // Switch turns
    }
    return codeResponse;
}

/**
 * Helper function to copy the state of the board from another board.
 * This function is used in the copy constructor and assignment operator.
 *
 * @param other The board to copy from.
 */
void Board::copyHelper(const Board& other) {
    isWhite = other.isWhite;
    board.resize(8, vector<Piece*>(8, nullptr)); // Initialize the board with nullptrs
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.board[i][j] != nullptr) {
                board[i][j] = other.board[i][j]->clone(); // Assuming Piece has a clone method
            }
        }
    }
    // Copy the king positions
    whiteKingPosition = other.whiteKingPosition;
    blackKingPosition = other.blackKingPosition;

    // Copy the king positions
    threats_to_white_king = new KingEnemies(true);
    threats_to_white_king->updateThreats(*this);
    threats_to_black_king = new KingEnemies(false);
    threats_to_black_king->updateThreats(*this);
}

/**
 * Copy constructor for the Board class.
 * Initializes a new board as a copy of another board.
 *
 * @param other The board to copy from.
 */
Board::Board(const Board& other) {
    copyHelper(other); // Copy the pieces from the other board
}

/**
 * Copy assignment operator for the Board class.
 * Assigns the state of one board to another.
 *
 * @param other The board to copy from.
 * @return A reference to the current board.
 */
Board &Board::operator=(const Board& other) {
    if(this != &other){
        // Free existing resources
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
            }
        }
        delete threats_to_white_king;
        delete threats_to_black_king;

        // Copy the state from the other board
        copyHelper(other); // Copy the pieces from the other board
    }
    return *this;
}

/**
 * Moves a piece from one position to another on the board.
 *
 * @param source The piece being moved.
 * @param startRow The starting row of the piece.
 * @param startCol The starting column of the piece.
 * @param endRow The target row of the piece.
 * @param endCol The target column of the piece.
 */
void Board::makeMove(Piece *source, int startRow, int startCol, int endRow, int endCol) {
    // Move the piece to the target square
    source->setNewCell(endRow, endCol);
    board[endRow][endCol] = source;
    board[startRow][startCol] = nullptr;
    // Update the king's threat tracking
    if(isWhite){
        if(source->getType() == KING){
            setWhiteKingPosition(endRow, endCol);
        }
        threats_to_white_king->updateThreats(*this);
    } else{
        if(source->getType() == KING) {
            setBlackKingPosition(endRow, endCol);
        }
        threats_to_black_king->updateThreats(*this);
    }
}

/**
 * Reverses a simulated move on the board.
 *
 * @param source The piece being moved.
 * @param target The piece being captured (if any).
 * @param startRow The starting row of the piece.
 * @param startCol The starting column of the piece.
 * @param endRow The target row of the piece.
 * @param endCol The target column of the piece.
 */
void Board::undoMove(Piece* source, Piece* target, int startRow, int startCol, int endRow, int endCol) {
    // Reversal simulated move
    source->setNewCell(startRow, startCol);
    board[startRow][startCol] = source;
    board[endRow][endCol] = target;
    // Update the king's threat tracking
    if(isWhite){
        if(source->getType() == KING){
            setWhiteKingPosition(startRow, startCol);
        }
        threats_to_white_king->updateThreats(*this);
    } else{
        if(source->getType() == KING) {
            setBlackKingPosition(startRow, startCol);
        }
        threats_to_black_king->updateThreats(*this);
    }
}

/**
 * Handles pawn promotion when a pawn reaches the last row.
 *
 * @param source The pawn being promoted.
 * @param newRow The new row of the pawn after promotion.
 * @param newCol The new column of the pawn after promotion.
 * @return True if the rival's king is in check after promotion, false otherwise.
 */
bool Board::HandlePromotion(Piece *source, int newRow, int newCol) {
    // Handle pawn promotion
    // Check if the soldier has reached the last line (Promotion)
    PieceColor sourceColor = source->getColor();
    if ((sourceColor == WHITE && newRow == 7) || (sourceColor == BLACK && newRow == 0)) {
        string choice;

        // Ask the user for their choice
        cout << "Pawn promotion! Choose a piece (queen, rook, bishop, knight): ";
        cin >> choice;

        // Delete the existing piece at the target position
        delete board[newRow][newCol];

        // Create a new piece based on the user's choice
        if (choice == "queen") {
            board[newRow][newCol] = new Queen(newRow, newCol, sourceColor);
        } else if (choice == "rook") {
            board[newRow][newCol] = new Rook(newRow, newCol, sourceColor);
        } else if (choice == "bishop") {
            board[newRow][newCol] = new Bishop(newRow, newCol, sourceColor);
        } else if (choice == "knight") {
            board[newRow][newCol] = new Knight(newRow, newCol, sourceColor);
        } else {
            cout << "Invalid choice! Defaulting to queen.\n";
            board[newRow][newCol] = new Queen(newRow, newCol, sourceColor);
        }
        // Update the King's threat tracking
        return IsRivalKingInCheck(board[newRow][newCol], newRow, newRow , newRow, newRow);
    }
    return false; // No promotion occurred
}

/**
 * Retrieves the top three recommended moves based on the current board state.
 * This function evaluates all possible moves using the EvaluateAllMoves class
 * @return A vector of strings representing the top three recommended moves.
 */
vector<string> Board::getTopMoves() {
    MyPriorityQueue<Move*> topMoves; // Priority queue to store the top moves
    EvaluateAllMoves e(3, *this); // Create an instance of EvaluateAllMoves

    vector<Move*> AllMoves = e.evaluateAllMoves(); // Evaluate all valid moves
    vector<string> bestMoves;
    try{
        for (Move *move: AllMoves) { // Iterate through all evaluated moves
            if (move->getScore() > 0) {
                topMoves.push(move); // Add the evaluated move to the priority queue
            }
        }
        topMoves.print(); // Print the moves in the priority queue

        // Get the top three moves from the priority queue
        while (!topMoves.empty() && bestMoves.size() < 3) { // Limit to top 3 moves
            ostringstream oss;
            oss << *topMoves.pull();
            string moveStr = oss.str();
            bestMoves.push_back(moveStr); // Retrieve the move with the highest score using poll()
        }
    } catch (PullFromEmptyQueueException& e) {
        cout << e.what() << endl; // Handle the exception if the queue is empty
    } catch (InvalidMoveException& e) {
        cout << e.what() << endl; // Handle the exception if the move is invalid
    }


    // Clean up the evaluated moves
    for (Move* move : AllMoves) {
        delete move; // Free memory allocated for each move
    }
    AllMoves.clear(); // Clear the vector of evaluated moves
    // Clear the priority queue
    topMoves.clear();

    return bestMoves;
}

