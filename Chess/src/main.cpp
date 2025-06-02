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

    if(gameMode == Constants::AUTOMATIC_MODE) {
        // Benchmark: run auto-game with varying thread counts
        for (int threads : {1, 2, 4, 8}) {
            Chess chess(board);
            double time = chess.measureAutoGameTime(searchDepth, Constants::NUMBER_OF_MOVES_FOR_AUTO_GAME, threads);
            std::cout << "=========================" << std::endl;
            std::cout << "Auto game with " << threads
                      << " threads (depth=" << searchDepth << ") took "
                      << time << " seconds." << std::endl;
            std::cout << "=========================" << std::endl;
        }
    }
    else {
        // Manual play mode
        Chess chess(board);
        chess.manualPlay(searchDepth);
    }

    return 0;
}