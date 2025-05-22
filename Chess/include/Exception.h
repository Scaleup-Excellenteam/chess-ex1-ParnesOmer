//
// Created by omer on 5/21/2025.
//

#ifndef CHESS_EXCEPTION_H
#define CHESS_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @class ChessException
 * @brief Base exception class for all custom exceptions in the chess project.
 *
 * Inherit from this class to create specific chess-related exceptions.
 * Stores an error message and provides an implementation for the what() method.
 */
class ChessException : public std::exception {
protected:
    std::string message;
public:
    /**
     * @brief Constructs a ChessException with the specified error message.
     * @param msg The error message to associate with the exception.
     */
    explicit ChessException(const std::string& msg) : message(msg) {}
    /**
     * @brief Returns a C-style character string describing the exception.
     * @return The error message.
     */
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class PullFromEmptyQueueException
 * @brief Exception thrown when attempting to pull from an empty priority queue.
 *
 * Use this exception to signal that a pull operation was attempted on a queue with no elements.
 */
class PullFromEmptyQueueException : public ChessException {
public:
    explicit PullFromEmptyQueueException() : ChessException("Cannot pull from an empty priority queue.") {}
};

/**
 * @class InvalidMoveException
 * @brief Exception thrown when attempting to push an invalid or null move into the queue.
 *
 * Use this exception to indicate that the move passed to push() is invalid or nullptr.
 */
class InvalidMoveException : public ChessException {
public:
    explicit InvalidMoveException(const std::string& msg = "Move is invalid or nullptr.") : ChessException(msg) {}
};

/**
 * @class BoardOutOfRange
 * @brief Exception thrown when attempting to access a board position that is out of range.
 *
 * Use this exception to indicate that the specified row or column is outside the valid range (0-7).
 */
class BoardOutOfRange : public ChessException {
public:
    explicit BoardOutOfRange(const std::string& msg = "Try to reach invalid or position.") : ChessException(msg) {}
};

#endif //CHESS_EXCEPTION_H
