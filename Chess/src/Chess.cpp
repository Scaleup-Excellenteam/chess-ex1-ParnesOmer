#include "Chess.h"
#include <iostream>
#include <string>

using namespace std;

// Platform-specific clear screen and board rendering
#ifdef _WIN32

// Clear Windows console screen
void Chess::clear() const {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

// create the GUI - ASCII art
void Chess::setFrames() {
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = 32;

	m_board[0][0] = 201;  m_board[0][20] = 187;
	m_board[20][0] = 200; m_board[20][20] = 188;

	for (size_t i = 1; i < 20; ++i) {
		m_board[0][i] = 205;
		m_board[20][i] = 205;
		m_board[i][0] = 186;
		m_board[i][20] = 186;
	} 

	m_board[2][2] = 218;  m_board[2][18] = 191;
	m_board[18][2] = 192; m_board[18][18] = 217;

	for (size_t i = 4; i < 17; i += 2) {
		m_board[2][i] = 194;
		m_board[18][i] = 193;
		m_board[i][2] = 195;
		m_board[i][18] = 180;
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = 196;

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = 179;

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = 197;

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = 194;
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = 193;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = 195;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = 180;

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('1' + t);

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('A' + t);
}

void Chess::setPieces() {
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? 32 : m_boardString[t]);
}

#else // non-Windows

void Chess::clear() const {
	cout << "\033[2J\033[3J\033[H";
}

void Chess::setFrames() {
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = ' ';

	m_board[0][0] = '+';
	m_board[0][20] = '+';
	m_board[20][0] = '+';
	m_board[20][20] = '+';

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = '-';
		m_board[20][i] = '-';
		m_board[i][0] = '|';
		m_board[i][20] = '|';
	}

	m_board[2][2] = '+';
	m_board[2][18] = '+';
	m_board[18][2] = '+';
	m_board[18][18] = '+';

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = '+';
		m_board[18][i] = '+';
		m_board[i][2] = '+';
		m_board[i][18] = '+';
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = '-';

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = '|';

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = '+';

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = '+';

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('1' + t);

	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('A' + t);
}

void Chess::setPieces() {
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? ' ' : m_boardString[t]);
}

#endif // WINDOWS


// Display the board
void Chess::show() const {
	for (size_t row = 0; row < _SIZE; ++row)
	{
		for (size_t col = 0; col < _SIZE; ++col)
			cout << m_board[row][col];
		cout << endl;
	}
}
// clear screen and print the board and the relevant msg 
void Chess::displayBoard() const {
	show();
	cout << m_msg<< m_errorMsg;
}

// Display board and messages
void Chess::showAskInput() const {
	if (m_turn)
		cout << "Player 1 (White - Capital letters) >> ";
	else
		cout << "Player 2 (Black - Small letters)   >> ";
}

// Returns true if source and destination squares are the same
bool Chess::isSame() const {
	return ((m_input[0] == m_input[2]) && (m_input[1] == m_input[3]));
}

// Validate format and range of input
bool Chess::isValid() const {
	return ((('A' <= m_input[0]) && (m_input[0] <= 'H')) || (('a' <= m_input[0]) && (m_input[0] <= 'h')) &&
		(('1' <= m_input[1]) && (m_input[1] <= '8')) &&
		(('A' <= m_input[2]) && (m_input[2] <= 'H')) || (('a' <= m_input[2]) && (m_input[2] <= 'h')) &&
		(('1' <= m_input[3]) && (m_input[3] <= '8')));
}

// Check if user wants to exit
bool Chess::isExit() const {
	return ((m_input == "exit") || (m_input == "quit") || (m_input == "EXIT") || (m_input == "QUIT"));
}

// Perform the move on the internal board string
void Chess::excute(int codeResponse) {
    // Handle pawn promotion
    if(codeResponse >= Constants::PROMOTION_MOVE_QUEEN &&
            codeResponse <= Constants::PROMOTION_CHECK_MOVE_KNIGHT){

        int startRow = (m_input[0] - 'a');
        int startCol = (m_input[1] - '1');
        char pieceInSource = m_boardString[(startRow * 8) + startCol];
        m_boardString[(startRow * 8) + startCol] = '#';

        int endRow = (m_input[2] - 'a');
        int endCol = (m_input[3] - '1');
        if(codeResponse == Constants::PROMOTION_MOVE_QUEEN || codeResponse == Constants::PROMOTION_CHECK_MOVE_QUEEN){
            m_boardString[(endRow * 8) + endCol] = std::isupper(pieceInSource) ? 'Q' : 'q';
        }
        else if(codeResponse == Constants::PROMOTION_MOVE_ROOK || codeResponse == Constants::PROMOTION_CHECK_MOVE_ROOK){
            m_boardString[(endRow * 8) + endCol] = std::isupper(pieceInSource) ? 'R' : 'r';
        }
        else if(codeResponse == Constants::PROMOTION_MOVE_BISHOP || codeResponse == Constants::PROMOTION_CHECK_MOVE_BISHOP){
            m_boardString[(endRow * 8) + endCol] = std::isupper(pieceInSource) ? 'B' : 'b';
        }
        else if(codeResponse == Constants::PROMOTION_MOVE_KNIGHT || codeResponse == Constants::PROMOTION_CHECK_MOVE_KNIGHT){
            m_boardString[(endRow * 8) + endCol] = std::isupper(pieceInSource) ? 'N' : 'n';
        }
    }
    // Handle castling moves
    else if(codeResponse >= Constants::CASTLE_RIGHT_NO_CHECK &&
            codeResponse <= Constants::CASTLE_LEFT_WITH_CHECK){

        int startRow = (m_input[0] - 'a');
        int startCol = (m_input[1] - '1');
        char pieceInSource = m_boardString[(startRow * 8) + startCol];
        m_boardString[(startRow * 8) + startCol] = '#';

        int endRow = (m_input[2] - 'a');
        int endCol = (m_input[3] - '1');
        if(codeResponse == Constants::CASTLE_RIGHT_NO_CHECK || codeResponse == Constants::CASTLE_RIGHT_WITH_CHECK){
            m_boardString[(endRow * 8) + endCol] = pieceInSource;
            m_boardString[(endRow * 8) + (endCol - 1)] = std::isupper(pieceInSource) ? 'R' : 'r';
            m_boardString[(endRow * 8) + (endCol + 1)] = '#'; // Clear the square between king and rook
        }
        else if (codeResponse == Constants::CASTLE_LEFT_NO_CHECK || codeResponse == Constants::CASTLE_LEFT_WITH_CHECK){
            m_boardString[(endRow * 8) + endCol] = pieceInSource;
            m_boardString[(endRow * 8) + (endCol + 1)] = std::isupper(pieceInSource) ? 'R' : 'r';
            m_boardString[(endRow * 8) + (endCol - 2)] = '#'; // Clear the square between king and rook
        }
    }
    else{
        int row = (m_input[0] - 'a');
        int col = (m_input[1] - '1');
        char pieceInSource = m_boardString[(row * 8) + col];
        m_boardString[(row * 8) + col] = '#';

        row = (m_input[2] - 'a');
        col = (m_input[3] - '1');
        m_boardString[(row * 8) + col] = pieceInSource;
    }
	setPieces(); 
}

// Handle move result codes, update messages, and switch turns if needed
void Chess::doTurn(int codeResponse) {
	m_errorMsg = "\n";
    if(codeResponse == 0){
        return; // No move made, exit early
    }

	switch (codeResponse)
	{
        case Constants::EMPTY_SOURCE:
        {
            m_msg = "there is not piece at the source \n";
            break;
        }
        case Constants::OPPONENT_PIECE:
        {
            m_msg = "the piece in the source is piece of your opponent \n";
            break;
        }
        case Constants::SAME_COLOR_PIECE:
        {
            m_msg = "there one of your pieces at the destination \n";
            break;
        }
        case Constants::ILLEGAL_MOVE:
        {
            m_msg = "illegal movement of that piece \n";
            break;
        }
        case Constants::CHECKMATE_MOVE:
        {
            m_msg = "this movement will cause you checkmate \n";
            break;
        }
        case Constants::MOVE_MADE_CHECK:
        {
            excute(codeResponse);
            m_turn = !m_turn;
            m_msg = "the last movement was legal and cause check \n";
            break;
        }
        case Constants::LEGAL_MOVE:
        {
            excute(codeResponse);
            m_turn = !m_turn;
            m_msg = "the last movement was legal \n";
            break;
        }
        default:
        {
            excute(codeResponse);
            m_turn = !m_turn;
            m_msg = "the last movement was legal \nCode response:" + std::to_string(codeResponse) + "\n";
            break;
        }
	}
}

// Constructor
Chess::Chess(const string& start) : m_boardString(start){
	setFrames();
	setPieces();
}

// Normalize move input to lowercase for file letters
void Chess::normalizeMove(std::string& move) {
    if (move.size() >= 4) {
        if ('A' <= move[0] && move[0] <= 'H')
            move[0] = move[0] - 'A' + 'a';
        if ('A' <= move[2] && move[2] <= 'H')
            move[2] = move[2] - 'A' + 'a';
    }
}

// Read user or auto move input; validate and normalize
string Chess::getInput(int codeResponse, bool isAutoMode, const std::string& autoMove) {
    if(isAutoMode) {
        doTurn(codeResponse);
        displayBoard();
        showAskInput();
        m_input = autoMove;
        if (isExit())
            return "exit";
    }
    else{
        static bool isFirst = true;
        if (isFirst)
            isFirst = false;
        else
            doTurn(codeResponse);

        displayBoard();
        showAskInput();

        cin >> m_input;
        if (isExit())
            return "exit";
        while (!isValid() || isSame()) {
            if (!isValid())
                m_errorMsg = "Invalid input !! \n";
            else
                m_errorMsg = "The source and the destination are the same !! \n";
            displayBoard();
            showAskInput();
            cin >> m_input;
            if (isExit())
                return "exit";
        }
    }
    normalizeMove(m_input);
    return m_input;
}

// Ask the user for the search depth (plies)
int Chess::askSearchDepth() {
    int searchDepth;
    std::cout << "Enter search depth (how many moves ahead to calculate): " << std::endl;
    while (std::cin >> searchDepth && searchDepth < 1) {
        std::cout << "Please enter a valid search depth (greater than 0): " << std::endl;
    }
    return searchDepth;
}

// Ask the user for the game mode (automatic/manual)
int Chess::askGameMode() {
    int gameMode;
    std::cout << "Select game mode: (1) Against the computer  (2) Two players: " << std::endl;
    while (cin >> gameMode && (gameMode != Constants::AGAINST_THE_COMPUTER && gameMode != Constants::TOW_PLAYERS)) {
        std::cout << "Please select a valid game mode (1 or 2): " << std::endl;
    }
    return gameMode;
}

// Against the computer
void Chess::againstTheComputer(int searchDepth, int numThreads) {
    std::cout << "Against The Computer mode selected. The AI will play against you." << std::endl;
    bool computerTurn = false;
    Board board;
    std::string res = getInput();
    int codeResponse = 0;
    while (res != "exit") {
        try {
            codeResponse = board.movePiece(res); // move the piece and get the code response
        }
        catch (invalid_argument&) {
            std::cout << "Invalid input !!" << std::endl;
            res = getInput();
            continue;
        }

        bool isInCheck = std::find(
                std::begin(Constants::MADE_CHECK_CODES),
                std::end(Constants::MADE_CHECK_CODES),
                codeResponse) != std::end(Constants::MADE_CHECK_CODES);

        if(codeResponse < Constants::CHECK_STATUS){
            res = getInput(codeResponse);
            continue;
        }

        // The move was legal, switch turns
        computerTurn = !computerTurn;

        // Show recommended moves
        std::vector<string> moves = board.getTopMoves(numThreads,searchDepth);
        if (moves.empty() && isInCheck) {
            if(board.getTurn()) {
                std::cout << "\nCheckmate!!! Black Won." << std::endl;
                break;
            } else if (!board.getTurn()) {
                std::cout << "\nCheckmate!!! White Won." << std::endl;
                break;
            }
        }
        if(computerTurn){
            printRecommendedMoves(moves);
            int spacePos = moves[0].find(' ');
            res = getInput(codeResponse, true, moves[0].substr(0, spacePos));
        }
        else {
            printRecommendedMoves(moves);
            res = getInput(codeResponse);
        }
    }

    std::cout << "\nExiting " << std::endl;
}

// Manual play mode
void Chess::manualPlay(int searchDepth, int numThreads) {
    std::cout << "Manual input mode selected. You can enter moves manually." << std::endl;
    Board board;
    int codeResponse = 0;
    string res = getInput();
    while (res != "exit") {
        try {
            codeResponse = board.movePiece(res); // move the piece and get the code response
        }
        catch (invalid_argument&) {
            std::cout << "Invalid input !!" << std::endl;
            res = getInput();
            continue;
        }

        bool isInCheck = std::find(
                std::begin(Constants::MADE_CHECK_CODES),
                std::end(Constants::MADE_CHECK_CODES),
                codeResponse) != std::end(Constants::MADE_CHECK_CODES);

        if(codeResponse > Constants::CHECK_STATUS) {  // if move was legal, show recommended moves
            std::vector<string> moves = board.getTopMoves(numThreads,searchDepth);
            if (moves.empty() && isInCheck) {
                if(board.getTurn()) {
                    std::cout << "\nCheckmate!!! Black Won." << std::endl;
                    break;
                } else if (!board.getTurn()) {
                    std::cout << "\nCheckmate!!! White Won." << std::endl;
                    break;
                }
            }
            printRecommendedMoves(moves);
        }
        res = getInput(codeResponse);
    }
    std::cout << "\nExiting " << std::endl;
}

// Print the top 3 recommended moves
void Chess::printRecommendedMoves(const vector<string> &moves) {
    std::cout << "\nTop three recommended moves: " << std::endl;
    for (const string &move: moves) {
        std::cout << "\t- " << move << std::endl;
    }
}
