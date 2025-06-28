// Chess
#include "Chess.h"


int main() {
    // Set up the standard chess board as a string
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    int searchDepth, gameMode;

    // Collect user input for search depth and game mode (automatic/manual)
    {
        Chess chess(board);
        searchDepth = chess.askSearchDepth();
        gameMode = chess.askGameMode();
    }

    if(gameMode == Constants::AGAINST_THE_COMPUTER) {
        // Against the computer mode
        Chess chess(board);
        chess.againstTheComputer(searchDepth, Constants::DEFAULT_NUM_THREADS);
    }
    else {
        // Manual play mode
        Chess chess(board);
        chess.manualPlay(searchDepth);
    }

    return 0;
}