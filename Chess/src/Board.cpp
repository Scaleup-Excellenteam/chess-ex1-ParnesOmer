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


Board::Board() : isWhite(true){
    board.resize(8, std::vector<Piece*>(8, nullptr));
    // Initialize the king positions
    whiteKingPosition = {0, 4}; // Initial position of the white king
    blackKingPosition = {7, 4}; // Initial position of the black king
    // Initialize the threats to the kings
    threats_to_white_king = new KingEnemies(true);
    threats_to_black_king = new KingEnemies(false);
    initializeBoard();
}


Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
    delete threats_to_white_king;
    delete threats_to_black_king;
}


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


const Piece* Board::getPiece(int row, int col) const {
    if(row < 0 || row >= 8 || col < 0 || col >= 8) {
        throw BoardOutOfRange();
    }
    return board[row][col];
}


Piece* Board::getPieceWithePermission(int row, int col) {
    if(row < 0 || row >= 8 || col < 0 || col >= 8) {
        throw BoardOutOfRange();
    }
    return board[row][col];
}


std::vector<Piece *> &Board::operator[](int row) {
    if(row < 0 || row >= 8) {
        throw BoardOutOfRange();
    }
    return board[row];
}


int Board::isValidMove(int startRow, int startCol , int endRow, int endCol) {
    Piece* source = board[startRow][startCol];
    Piece* target = board[endRow][endCol];

    // The source square is empty
    if(source == nullptr){
        return Constants::EMPTY_SOURCE;
    }

    PieceColor sourceColor = source->getColor();

    // The piece in the source square belongs to the opposing player
    if(sourceColor != isWhite){
        return Constants::OPPONENT_PIECE;
    }

    // The target square contains a piece of the same player
    if(target != nullptr && sourceColor == target->getColor()) {
        return Constants::SAME_COLOR_PIECE;
    }

    // Check if the move complies with the piece's movement rules
    if(!source->isValidMove(startRow, startCol, endRow, endCol, *this)){
        return Constants::ILLEGAL_MOVE;
    }

    // Simulate the move
    makeMove(source, startRow, startCol, endRow, endCol);

    // Check if the move leaves the player's king in check
    if(King_in_check(isWhite)){
        // Reversal simulated move
        undoMove(source, target, startRow, startCol, endRow, endCol);
        return Constants::CHECKMATE_MOVE;
    }

    // Check if the move puts the rival's king in check
    if(IsRivalKingInCheck(source, startRow, startCol, endRow, endCol)){
        // Reversal simulated move
        undoMove(source, target, startRow, startCol, endRow, endCol);
        return Constants::MOVE_MADE_CHECK;
    }

    // Reversal simulated move
    undoMove(source, target, startRow, startCol, endRow, endCol);
    return Constants::LEGAL_MOVE;
}


bool Board::IsRivalKingInCheck(const Piece *sourcePiece, int startRow, int startCol , int endRow, int endCol) {
    // Checks whether the move added a threat to the enemy's king
    if(isWhite){
        threats_to_black_king->updateThreatsOnMove(sourcePiece, startRow, startCol, endRow, endCol, *this);
    }else{
        threats_to_white_king->updateThreatsOnMove(sourcePiece, startRow, startCol, endRow, endCol, *this);
    }

    return King_in_check(!isWhite);
}


bool Board::King_in_check(bool whichKing) const {
    if (whichKing) {
        return threats_to_white_king->isKingInCheck(*this);
    } else {
        return threats_to_black_king->isKingInCheck(*this);
    }
}


int Board::movePiece(const std::string& moveInput) {
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
    if (codeResponse > Constants::CHECK_STATUS) {  // If the move was successful
        makeMove(source, startRow, startCol, endRow, endCol);
        if(codeResponse == Constants::LEGAL_MOVE && source->getType() == PAWN) {
            // Pawn promotion
            codeResponse = HandlePromotion(source, endRow, endCol);
        }
        if(source->getType() == KING){
            if((endCol - startCol) == 2){
                codeResponse = (codeResponse == 41) ? Constants::CASTLE_RIGHT_WITH_CHECK : Constants::CASTLE_RIGHT_NO_CHECK;
            }
            else if(endCol - startCol == -2) {
                codeResponse = (codeResponse == 41) ? Constants::CASTLE_LEFT_WITH_CHECK : Constants::CASTLE_LEFT_NO_CHECK;
            }
        }

        isWhite = !isWhite; // Switch turns
    }
    return codeResponse;
}


void Board::copyHelper(const Board& other) {
    isWhite = other.isWhite;
    board.resize(8, std::vector<Piece*>(8, nullptr)); // Initialize the board with nullptrs
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


Board::Board(const Board& other) {
    copyHelper(other); // Copy the pieces from the other board
}


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


void Board::makeMove(Piece *source, int startRow, int startCol, int endRow, int endCol) {
    // Move the piece to the target square
    source->setNewCell(endRow, endCol);
    board[endRow][endCol] = source;
    board[startRow][startCol] = nullptr;
    // Update the king's threat tracking
    if(isWhite){
        if(source->getType() == KING){
            whiteKingMoved++; // Increment the white king moved counter
            setWhiteKingPosition(endRow, endCol);
            if((endCol - startCol) == 2) {
                Piece* rightRook = board[0][7];
                rightRook->setNewCell(0, 5);
                board[0][5] = rightRook; // Move the right rook to the new position
                board[0][7] = nullptr; // Remove the right rook from its original position
                WhiteRookStatus.second++; // Right rook
            } else if(endCol - startCol == -2) { // Left castle
                Piece* leftRook = board[0][0];
                leftRook->setNewCell(0, 3);
                board[0][3] = leftRook; // Move the left rook to the new position
                board[0][0] = nullptr; // Remove the left rook from its original position
                WhiteRookStatus.first++; // Left rook
            }
        }
        else if(source->getType() == ROOK) {
            if(startCol == 0) WhiteRookStatus.first++; // Left rook
            else if(startCol == 7) WhiteRookStatus.second++; // Right rook
        }
        threats_to_white_king->updateThreats(*this);
    } else{
        if(source->getType() == KING) {
            blackKingMoved++; // Increment the black king moved counter
            setBlackKingPosition(endRow, endCol);

            if((endCol - startCol) == 2) {
                Piece* rightRook = board[7][7];
                rightRook->setNewCell(7, 5);
                board[7][5] = rightRook; // Move the right rook to the new position
                board[7][7] = nullptr; // Remove the right rook from its original position
                BlackRookStatus.second++; // Right rook
            } else if(endCol - startCol == -2) { // Left castle
                Piece* leftRook = board[7][0];
                leftRook->setNewCell(7, 3);
                board[7][3] = leftRook; // Move the left rook to the new position
                board[7][0] = nullptr; // Remove the left rook from its original position
                BlackRookStatus.first++; // Left rook
            }
        }
        else if(source->getType() == ROOK) {
            if(startCol == 0) BlackRookStatus.first++; // Left rook
            else if(startCol == 7) BlackRookStatus.second++; // Right rook
        }
        threats_to_black_king->updateThreats(*this);
    }
}


void Board::undoMove(Piece* source, Piece* target, int startRow, int startCol, int endRow, int endCol) {
    // Reversal simulated move
    source->setNewCell(startRow, startCol);
    board[startRow][startCol] = source;
    board[endRow][endCol] = target;
    // Update the king's threat tracking
    if(isWhite){
        if(source->getType() == KING){
            whiteKingMoved--; // Decrement the white king moved counter
            setWhiteKingPosition(startRow, startCol);

            if((endCol - startCol) == 2) {
                Piece* rightRook = board[0][5];
                rightRook->setNewCell(0, 7);
                board[0][7] = rightRook; // Move the right rook back to its original position
                board[0][5] = nullptr; // Remove the right rook from its new position
                WhiteRookStatus.second--; // Right rook
            } else if(endCol - startCol == -2) { // Left castle
                Piece* leftRook = board[0][3];
                leftRook->setNewCell(0, 0);
                board[0][0] = leftRook; // Move the left rook back to its original position
                board[0][3] = nullptr; // Remove the left rook from its new position
                WhiteRookStatus.first--; // Left rook
            }
        }
        else if(source->getType() == ROOK) {
            if(startCol == 0) WhiteRookStatus.first--; // Left rook
            else if(startCol == 7) WhiteRookStatus.second--; // Right rook
        }
        threats_to_white_king->updateThreats(*this);
    } else{
        if(source->getType() == KING) {
            blackKingMoved--; // Decrement the black king moved counter
            setBlackKingPosition(startRow, startCol);

            if((endCol - startCol) == 2) {
                Piece* rightRook = board[7][5];
                rightRook->setNewCell(7, 7);
                board[7][7] = rightRook; // Move the right rook back to its original position
                board[7][5] = nullptr; // Remove the right rook from its new position
                BlackRookStatus.second--; // Right rook
            } else if(endCol - startCol == -2) { // Left castle
                Piece* leftRook = board[7][3];
                leftRook->setNewCell(7, 0);
                board[7][0] = leftRook; // Move the left rook back to its original position
                board[7][3] = nullptr; // Remove the left rook from its new position
                BlackRookStatus.first--; // Left rook
            }
        }
        else if(source->getType() == ROOK) {
            if(startCol == 0) BlackRookStatus.first--; // Left rook
            else if(startCol == 7) BlackRookStatus.second--; // Right rook
        }
        threats_to_black_king->updateThreats(*this);
    }
}


int Board::HandlePromotion(Piece *source, int newRow, int newCol) {
    // Handle pawn promotion
    // Check if the soldier has reached the last line (Promotion)
    PieceColor sourceColor = source->getColor();
    int promotionStatus = Constants::LEGAL_MOVE; // Promotion status code

    if ((sourceColor == WHITE && newRow == 7) || (sourceColor == BLACK && newRow == 0)) {
        std::string choice;
        // Ask the user for their choice
        std::cout << "Pawn promotion! Choose a piece (queen, rook, bishop, knight): ";
        std::cin >> choice;

        // Delete the existing piece at the target position
        delete board[newRow][newCol];

        // Create a new piece based on the user's choice
        if (choice == "queen") {
            board[newRow][newCol] = new Queen(newRow, newCol, sourceColor);
            promotionStatus = Constants::PROMOTION_MOVE_QUEEN;
        } else if (choice == "rook") {
            board[newRow][newCol] = new Rook(newRow, newCol, sourceColor);
            promotionStatus = Constants::PROMOTION_MOVE_ROOK;
        } else if (choice == "bishop") {
            board[newRow][newCol] = new Bishop(newRow, newCol, sourceColor);
            promotionStatus = Constants::PROMOTION_MOVE_BISHOP;
        } else if (choice == "knight") {
            board[newRow][newCol] = new Knight(newRow, newCol, sourceColor);
            promotionStatus = Constants::PROMOTION_MOVE_KNIGHT;
        } else {
            std::cout << "Invalid choice! Defaulting to queen.\n";
            board[newRow][newCol] = new Queen(newRow, newCol, sourceColor);
            promotionStatus = Constants::PROMOTION_MOVE_QUEEN;
        }
        // Update the King's threat tracking
        if(IsRivalKingInCheck(board[newRow][newCol], newRow, newRow , newRow, newRow)){
            return promotionStatus + 10;
        }
    }
    return promotionStatus;
}


std::vector<std::string> Board::getTopMoves(int numThreads, int depth) {
    EvaluateAllMoves e(depth, *this); // Create an instance of EvaluateAllMoves

    MyPriorityQueue<std::unique_ptr<Move>> topMoves = e.evaluateAllMoves(numThreads); // Evaluate all valid moves
    std::vector<std::string> bestMoves;

    try{
        //topMoves.print(); // Print the moves in the priority queue for debugging purposes

        // Get the top three moves from the priority queue
        while (!topMoves.empty() && bestMoves.size() < 3) { // Limit to top 3 moves
            auto movePtr = topMoves.pull();
            std::ostringstream oss;
            oss << *movePtr;
            bestMoves.push_back(oss.str()); // Retrieve the move with the highest score using poll()
        }
    } catch (PullFromEmptyQueueException& e) {
        std::cout << e.what() << std::endl; // Handle the exception if the queue is empty
    } catch (InvalidMoveException& e) {
        std::cout << e.what() << std::endl; // Handle the exception if the move is invalid
    }

    return bestMoves;
}

//the king cannot be in check when calling this function
bool Board::whiteKingCanCastle(bool rightCastle) const {
    if(rightCastle){
        if(WhiteRookStatus.second > 0 || whiteKingMoved) {
            return false; // Right rook has moved or king has moved
        }
        // Check if the squares between the king and rook are empty
        for(int col = 5; col <= 6; ++col) {
            if(board[0][col] != nullptr) {
                return false;
            }
        }
    }
    else {
        // Check if the left rook has moved
        if (WhiteRookStatus.first || whiteKingMoved) {
            return false;
        }
        // Check if the squares between the king and rook are empty
        for (int col = 1; col <= 3; ++col) {
            if (board[0][col] != nullptr) {
                return false;
            }
        }
    }
    return true; // The king can castle
}


bool Board::blackKingCanCastle(bool rightCastle) const  {
    if(rightCastle){
        if(BlackRookStatus.second > 0 || blackKingMoved) {
            return false; // Right rook has moved or king has moved
        }
        // Check if the squares between the king and rook are empty
        for(int col = 5; col <= 6; ++col) {
            if(board[7][col] != nullptr) {
                return false;
            }
        }
    }
    else{
        // Check if the left rook has moved
        if (BlackRookStatus.first || blackKingMoved) {
            return false;
        }
        // Check if the squares between the king and rook are empty
        for (int col = 1; col <= 3; ++col) {
            if (board[7][col] != nullptr) {
                return false;
            }
        }
    }
    return true; // The king can castle
}