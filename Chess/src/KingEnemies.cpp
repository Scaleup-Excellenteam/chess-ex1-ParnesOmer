//
// Created by omer on 4/14/2025.
//

#include "KingEnemies.h"

KingEnemies::KingEnemies(int x, int y)  : KingX(x), KingY(y){}

void KingEnemies::updateThreats(const Board& board) {
    // Clean up previous threats
    threat_from_pawn.clear();
    threat_from_queen.clear();
    threat_from_knight.clear();
    threat_from_bishop.clear();
    threat_from_rook.clear();

    const Piece* myKing = board.getPiece(KingX, KingY);
    // Go over the entire board and check for threats
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const Piece* piece = board.getPiece(i, j);
            if (piece != nullptr && piece->getColor() != myKing->getColor() && piece->isThreat(i, j, KingX, KingY)) {
                switch (piece->getType()) {
                    case PAWN: threat_from_pawn.push_back(const_cast<Piece*>(piece)); break;
                    case QUEEN: threat_from_queen.push_back(const_cast<Piece*>(piece)); break;
                    case KNIGHT: threat_from_knight.push_back(const_cast<Piece*>(piece)); break;
                    case BISHOP: threat_from_bishop.push_back(const_cast<Piece*>(piece)); break;
                    case ROOK: threat_from_rook.push_back(const_cast<Piece*>(piece)); break;
                    default: break;
                }
            }
        }
    }
}

// Function to check if the path is free
bool isPathClear(int startX, int startY, int endX, int endY, const Board& board) {
    int dx = (endX - startX) == 0 ? 0 : (endX - startX) / abs(endX - startX);
    int dy = (endY - startY) == 0 ? 0 : (endY - startY) / abs(endY - startY);

    int x = startX + dx;
    int y = startY + dy;

    while (x != endX || y != endY) {
        if (board.getPiece(x, y) != nullptr) {
            return false; // The path is blocked
        }
        x += dx;
        y += dy;
    }
    return true; // The path is clear
}

bool KingEnemies::isKingInCheck(const Board& board) const {
    // Check for pedestrians and horses (doesn't need a clear path)
//    for (const auto& pawn : threat_from_pawn) {
//        if (pawn->isThreat(pawn->getX(), pawn->getY(), KingX, KingY)) {
//            return true;
//        }
//    }
//
//    for (const auto& knight : threat_from_knight) {
//        if (knight->isThreat(knight->getX(), knight->getY(), KingX, KingY)) {
//            return true;
//        }
//    }
    if(!threat_from_pawn.empty() || !threat_from_knight.empty()){
        return true;
    }

    // Check for tools that require a clear path
    if(!threat_from_rook.empty()){
        for (const auto& rook : threat_from_rook) {
            if (isPathClear(rook->getX(), rook->getY(), KingX, KingY, board)) {
                return true;
            }
        }
    }

    if(!threat_from_bishop.empty()) {
        for (const auto &bishop: threat_from_bishop) {
            if (isPathClear(bishop->getX(), bishop->getY(), KingX, KingY, board)) {
                return true;
            }
        }
    }

    if(!threat_from_queen.empty()) {
        for (const auto &queen: threat_from_queen) {
            if (isPathClear(queen->getX(), queen->getY(), KingX, KingY, board)) {
                return true;
            }
        }
    }
    return false; // There is no active threat to the king
}

void KingEnemies::kingMoved(int x, int y, const Board& board) {
    KingX = x;
    KingY = y;
    updateThreats(board);
}

void KingEnemies::updateThreatsOnMove(const Piece *movedPiece, int oldX, int oldY, int newX, int newY, const Board &board) {
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

    // 2. Checking if the new piece threatens the king
    const Piece* myKing = board.getPiece(KingX, KingY);
    if (movedPiece != nullptr && movedPiece->isThreat(newX, newY, KingX, KingY)) {
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

