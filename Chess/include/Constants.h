//
// Created by omer on 5/27/2025.
//

#ifndef CHESS_CONSTANTS_H
#define CHESS_CONSTANTS_H

namespace Constants {
    constexpr int PRIORITY_QUEUE_SIZE = 5; // Size of the priority queue for move evaluation
    constexpr int CHECK_STATUS = 40; // Move that checks if the move is valid
    constexpr int NUMBER_OF_MOVES_FOR_AUTO_GAME = 8; // Number of moves to simulate in automatic game mode
    constexpr int AUTOMATIC_MODE = 1; // Automatic mode for the game
    constexpr int MANUAL_MODE = 2; // Manual input mode for the game
    constexpr int HIGH_SCORE_THRESHOLD = 15; // Threshold for high scoring moves in evaluation
}

#endif //CHESS_CONSTANTS_H
