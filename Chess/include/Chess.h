#pragma once
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "Constants.h"
#include "Board.h"
#include <string>
#include <chrono>

using std::cout;
using std::cin; 
using std::endl;
using std::string; 

const int _SIZE = 21;

class Chess {
	unsigned char m_board[_SIZE][_SIZE] = { 0 };
	bool m_turn = true;
	string m_boardString;
	string m_input;
	string m_msg = "\n";
	string m_errorMsg = "\n";
	int m_codeResponse;

	void clear() const;
	void setFrames();
	void setPieces();
	void show() const;
	void displayBoard() const;
	void showAskInput() const;
	bool isSame() const;
	bool isValid() const;
	bool isExit() const;
	void excute();
	void doTurn();

public:
	Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	Chess(const Chess&)=delete;
	Chess& operator=(const Chess&) = delete;
	string getInput(bool isAutoMode, const std::string& nextMove = "");
	void setCodeResponse(int codeResponse);

    void normalizeMove(std::string& move);
    int askSearchDepth();
    int askGameMode();
    void autoPlay(int searchDepth, int numMoves, int numThreads);
    void manualPlay(int searchDepth, int numThreads = 1);
    void printRecommendedMoves(const vector<string>& moves);
    double measureAutoGameTime(int searchDepth, int numMoves, int numThreads);
};