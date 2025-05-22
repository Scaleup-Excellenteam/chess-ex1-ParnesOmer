//
// Created by omer on 4/14/2025.
//

#include "KingEnemies.h"

/**
 * Constructor for the KingEnemies class.
 * Initializes the class with the king's initial position.
 *
 * @param row The row position of the king.
 * @param col The column position of the king.
 */
KingEnemies::KingEnemies(bool isWhite)  : isWhite(isWhite){}

/**
 * Destructor for the KingEnemies class.
 * Frees all dynamically allocated memory for threat vectors.
 */
KingEnemies::~KingEnemies() = default;

/**
 * Helper function to copy the state of the KingEnemies object.
 * This function is not used in the current implementation but can be
 * useful for deep copying if needed in the future.
 *
 * @param other The KingEnemies object to copy from.
 */
void KingEnemies::copyHelper(const KingEnemies &other) {
    isWhite = other.isWhite;
    for (const Piece* piece : other.threat_from_pawn) {
        threat_from_pawn.push_back(piece);
    }
    for (const Piece* piece : other.threat_from_queen) {
        threat_from_queen.push_back(piece);
    }
    for (const Piece* piece : other.threat_from_knight) {
        threat_from_knight.push_back(piece);
    }
    for (const Piece* piece : other.threat_from_bishop) {
        threat_from_bishop.push_back(piece);
    }
    for (const Piece* piece : other.threat_from_rook) {
        threat_from_rook.push_back(piece);
    }
}


/**
 * Copy constructor for the KingEnemies class.
 * Performs a deep copy of all threat vectors and other members.
 *
 * @param other The KingEnemies object to copy from.
 */
KingEnemies::KingEnemies(const KingEnemies& other){
    copyHelper(other);
}


/**
 * Copy assignment operator for the KingEnemies class.
 * Performs a deep copy of all threat vectors and other members.
 *
 * @param other The KingEnemies object to copy from.
 * @return A reference to the current KingEnemies object.
 */
KingEnemies& KingEnemies::operator=(const KingEnemies& other) {
    if (this != &other) { // Check for self-assignment
        // Clear existing resources
        threat_from_pawn.clear();
        threat_from_queen.clear();
        threat_from_knight.clear();
        threat_from_bishop.clear();
        threat_from_rook.clear();

        // Copy the state from the other object
        copyHelper(other);
    }
    return *this;
}

/**
 * Gets the current position of the king based on its color.
 * If the king is white, it retrieves the white king's position; otherwise, it retrieves the black king's position.
 *
 * @param board The current state of the chessboard.
 * @return A pair representing the row and column of the king's position.
 */
pair<int, int> KingEnemies::getKingPosition(const Board& board) const {
    if(isWhite) {
        return board.getWhiteKingPosition();
    } else {
        return board.getBlackKingPosition();
    }

}

/**
 * Updates the threats to the king by analyzing the entire chessboard.
 * Clears previous threats and recalculates based on the current state of the board.
 *
 * @param board The current state of the chessboard.
 */
void KingEnemies::updateThreats(const Board& board) {
    // Clean up previous threats
    threat_from_pawn.clear();
    threat_from_queen.clear();
    threat_from_knight.clear();
    threat_from_bishop.clear();
    threat_from_rook.clear();

    // Get the current position of the king
    auto [KingRow, KingCol] = getKingPosition(board);

    const Piece* myKing = board.getPiece(KingRow, KingCol);
    if (myKing == nullptr) {
        cout << "King not found on the board! is white? :" << isWhite << endl;
        return; // King not found, no threats to update
    }
    // Go over the entire board and check for threats
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const Piece* piece = board.getPiece(i, j);
            if (piece != nullptr && piece->getColor() != myKing->getColor() && piece->isThreat(i, j, KingRow, KingCol)) {
                switch (piece->getType()) {
                    case PAWN: threat_from_pawn.push_back(piece); break;
                    case QUEEN: threat_from_queen.push_back(piece); break;
                    case KNIGHT: threat_from_knight.push_back(piece); break;
                    case BISHOP: threat_from_bishop.push_back(piece); break;
                    case ROOK: threat_from_rook.push_back(piece); break;
                    default: break;
                }
            }
        }
    }
}

/**
 * Checks if the path between two positions is clear of any pieces.
 *
 * @param startRow The starting row.
 * @param startCol The starting column.
 * @param endRow The target row.
 * @param endCol The target column.
 * @param board The current state of the chessboard.
 * @return True if the path is clear, false otherwise.
 */bool KingEnemies::isPathClear(int startRow, int startCol, int endRow, int endCol, const Board& board) {
    int dx = (endRow - startRow) == 0 ? 0 : (endRow - startRow) / abs(endRow - startRow);
    int dy = (endCol - startCol) == 0 ? 0 : (endCol - startCol) / abs(endCol - startCol);

    int x = startRow + dx;
    int y = startCol + dy;

    while (x != endRow || y != endCol) {
        if(x < 0 || x >= 8 || y < 0 || y >= 8) {
            return false; // Out of bounds
        }
        if (board.getPiece(x, y) != nullptr) {
            return false; // The path is blocked
        }
        x += dx;
        y += dy;
    }
    return true; // The path is clear
}

/**
 * Determines if the king is currently in check.
 *
 * @param board The current state of the chessboard.
 * @return True if the king is in check, false otherwise.
 */
bool KingEnemies::isKingInCheck(const Board& board) const {
    // Check for pawns and knights (doesn't need a clear path)
    if(!threat_from_pawn.empty() || !threat_from_knight.empty()){
        return true;
    }

    // Get the current position of the king
    auto [KingRow, KingCol] = getKingPosition(board);

    // Check for tools that require a clear path
    if(!threat_from_rook.empty()){
        for (const auto& rook : threat_from_rook) {
            if (isPathClear(rook->getX(), rook->getY(), KingRow, KingCol, board)) {
                return true;
            }
        }
    }

    if(!threat_from_bishop.empty()) {
        for (const auto &bishop: threat_from_bishop) {
            if (isPathClear(bishop->getX(), bishop->getY(), KingRow, KingCol, board)) {
                return true;
            }
        }
    }

    if(!threat_from_queen.empty()) {
        for (const auto &queen: threat_from_queen) {
            if (isPathClear(queen->getX(), queen->getY(), KingRow, KingCol, board)) {
                return true;
            }
        }
    }
    return false; // There is no active threat to the king
}

/**
 * Updates the threats when a piece is moved on the chessboard.
 *
 * @param movedPiece The piece that was moved.
 * @param oldRow The original row of the moved piece.
 * @param oldCol The original column of the moved piece.
 * @param newRow The new row of the moved piece.
 * @param newCol The new column of the moved piece.
 * @param board The current state of the chessboard.
 */
void KingEnemies::updateThreatsOnMove(const Piece *movedPiece, int oldRow, int oldCol, int newRow, int newCol, const Board &board) {
    // 1. Removing the old threat (if any)
    if (movedPiece != nullptr) {
        switch (movedPiece->getType()) {
            case PAWN:
                threat_from_pawn.erase(std::remove(threat_from_pawn.begin(), threat_from_pawn.end(), movedPiece), threat_from_pawn.end());
                break;
            case ROOK:
                threat_from_rook.erase(std::remove(threat_from_rook.begin(), threat_from_rook.end(), movedPiece), threat_from_rook.end());
                break;
            case KNIGHT:
                threat_from_knight.erase(std::remove(threat_from_knight.begin(), threat_from_knight.end(), movedPiece), threat_from_knight.end());
                break;
            case BISHOP:
                threat_from_bishop.erase(std::remove(threat_from_bishop.begin(), threat_from_bishop.end(), movedPiece), threat_from_bishop.end());
                break;
            case QUEEN:
                threat_from_queen.erase(std::remove(threat_from_queen.begin(), threat_from_queen.end(), movedPiece), threat_from_queen.end());
                break;
            default: break;
        }
    }

    // Get the current position of the king
    auto [KingRow, KingCol] = getKingPosition(board);

    // 2. Checking if the new piece threatens the king
    if (movedPiece != nullptr && movedPiece->isThreat(newRow, newCol, KingRow, KingCol)) {
        switch (movedPiece->getType()) {
            case PAWN:
                threat_from_pawn.push_back(const_cast<Piece*>(movedPiece));
                break;
            case ROOK:
                threat_from_rook.push_back(const_cast<Piece*>(movedPiece));
                break;
            case KNIGHT:
                threat_from_knight.push_back(const_cast<Piece*>(movedPiece));
                break;
            case BISHOP:
                threat_from_bishop.push_back(const_cast<Piece*>(movedPiece));
                break;
            case QUEEN:
                threat_from_queen.push_back(const_cast<Piece*>(movedPiece));
                break;
            default: break;
        }
    }
}
