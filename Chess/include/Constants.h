//
// Created by omer on 5/27/2025.
//

#ifndef CHESS_CONSTANTS_H
#define CHESS_CONSTANTS_H


namespace Constants {
    // Constants for code responses
    constexpr int CHECK_STATUS = 40;                // Move that checks if the move is valid

    constexpr int EMPTY_SOURCE = 11;                // There is no piece at the source
    constexpr int OPPONENT_PIECE = 12;              // The piece in the source is a piece of your opponent
    constexpr int SAME_COLOR_PIECE = 13;            // There is one of your pieces at the destination
    constexpr int ILLEGAL_MOVE = 21;                // Illegal movement of that piece
    constexpr int CHECKMATE_MOVE = 31;              // This movement will cause you checkmate
    constexpr int MOVE_MADE_CHECK = 41;             // The last movement was legal and caused check
    constexpr int LEGAL_MOVE = 42;                  // The last movement was legal

    constexpr int PROMOTION_MOVE_QUEEN = 52;        // Pawn promotion move
    constexpr int PROMOTION_MOVE_ROOK = 53;         // Pawn promotion move to rook
    constexpr int PROMOTION_MOVE_BISHOP = 54;       // Pawn promotion move to bishop
    constexpr int PROMOTION_MOVE_KNIGHT = 55;       // Pawn promotion move to knight
    constexpr int PROMOTION_CHECK_MOVE_QUEEN = 62;  // Pawn promotion move that checks the king with queen
    constexpr int PROMOTION_CHECK_MOVE_ROOK = 63;   // Pawn promotion move that checks the king with rook
    constexpr int PROMOTION_CHECK_MOVE_BISHOP = 64; // Pawn promotion move that checks the king with bishop
    constexpr int PROMOTION_CHECK_MOVE_KNIGHT = 65; // Pawn promotion move that checks the king with knight

    constexpr int CASTLE_RIGHT_NO_CHECK = 71;       // Right castle move
    constexpr int CASTLE_LEFT_NO_CHECK = 72;        // Left castle move
    constexpr int CASTLE_RIGHT_WITH_CHECK = 81;     // Right castle move that checks the king
    constexpr int CASTLE_LEFT_WITH_CHECK = 82;      // Left castle move that checks the king

    constexpr int MADE_CHECK_CODES[] = {
            Constants::PROMOTION_CHECK_MOVE_QUEEN,
            Constants::PROMOTION_CHECK_MOVE_ROOK,
            Constants::PROMOTION_CHECK_MOVE_BISHOP,
            Constants::PROMOTION_CHECK_MOVE_KNIGHT,
            Constants::CASTLE_RIGHT_WITH_CHECK,
            Constants::CASTLE_LEFT_WITH_CHECK,
            Constants::MOVE_MADE_CHECK
    };

    // Constants for chess piece values
    constexpr int ROOK_VALUE = 5;
    constexpr int BISHOP_VALUE = 3;
    constexpr int KNIGHT_VALUE = 3;
    constexpr int QUEEN_VALUE = 9;
    constexpr int PAWN_VALUE = 1;

    constexpr int PRIORITY_QUEUE_SIZE = 5;          // Size of the priority queue for move evaluation
    constexpr int AGAINST_THE_COMPUTER = 1;         // Automatic mode for the game
    constexpr int TOW_PLAYERS = 2;                  // Manual input mode for the game
    constexpr int HIGH_SCORE_THRESHOLD = 9000;      // Threshold for high scoring moves in evaluation
    constexpr int DEFAULT_SEARCH_DEPTH = 3;         // Default search depth for move evaluation
    constexpr int DEFAULT_NUM_THREADS = 8;          // Default number of threads for parallel evaluation
}

#endif //CHESS_CONSTANTS_H
