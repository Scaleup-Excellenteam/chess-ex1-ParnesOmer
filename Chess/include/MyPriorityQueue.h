//
// Created by omer on 5/10/2025.
//

#ifndef CHESS_MYPRIORITYQUEUE_H
#define CHESS_MYPRIORITYQUEUE_H

#include "Exception.h"
#include "Constants.h"
#include <list>
#include <stdexcept>
#include <iostream>


/**
 * @brief Comparator struct for comparing two chess moves.
 * Assumes T is a pointer type and operator< is overloaded for the pointed type.
 */
template<typename T>
struct MyComparator {
    /**
     * @brief Returns true if move 'a' has lower priority than move 'b'.
     * @param a First move pointer.
     * @param b Second move pointer.
     * @return True if *a < *b.
     */
    bool operator()(const T& a, const T& b) const {
        return (*a) < (*b);
    }
};

/**
 * @brief Priority queue for chess moves.
 * Elements with higher priority (as defined by operator<) are pulled first.
 * Uses a sorted std::list internally.
 * Assumes T is a pointer type (e.g., Move*), and operator< is overloaded for its pointed type.
 */
template<typename T>
class MyPriorityQueue{
    std::list<T> queue;                ///< Internal queue, sorted by priority.
    MyComparator<T> comparator;  ///< Comparator instance.
public:
    /**
     * @brief Default constructor.
     */
    MyPriorityQueue() = default;
    /**
     * @brief Default destructor.
     */
    ~MyPriorityQueue() = default;
    MyPriorityQueue(const MyPriorityQueue&) = delete;
    MyPriorityQueue& operator=(const MyPriorityQueue&) = delete;
    MyPriorityQueue(MyPriorityQueue&&) = default;
    MyPriorityQueue& operator=(MyPriorityQueue&&) = default;

    /**
     * @brief Push a new move into the queue, maintaining priority order.
     * @param move Pointer to the move to insert. Must not be nullptr.
     * @throws std::invalid_argument if move is nullptr.
     */
    void push(T&& move) {
        if (!move) {
            throw InvalidMoveException();  // Move is nullptr
        }
        // Find correct position to insert the move by priority
        auto it = queue.begin();
        while (it != queue.end() && comparator(move, *it)) {
            ++it;
        }
        queue.insert(it, std::move(move)); // Insert the move at the correct position
        if(queue.size() > Constants::PRIORITY_QUEUE_SIZE) {
            queue.pop_back(); // Remove the lowest priority move if the queue exceeds the size limit
        }
    }

    /**
     * @brief Pull (and remove) the highest priority move from the queue.
     * @return Pointer to the move with the highest priority, or nullptr if the queue is empty.
     */
    T pull() {
        if (queue.empty()) {
            throw PullFromEmptyQueueException(); // Cant pull from an empty queue
        }
        // Pulling the first element
        T highest = std::move(queue.front());
        queue.pop_front(); // remove it from the queue
        return highest;
    }

    /**
     * @brief Print all moves in the queue (in priority order).
     * The function exist for debugging purposes.
     * Assumes operator<< is overloaded for the pointed type.
     */
    void print() const {
        for (const auto& move : queue) {
            std::cout << *move << std::endl; // Print each move in the queue
        }
    }
    /**
     * @brief Clear the queue, removing all moves.
     */
    void clear() {
        queue.clear(); // clear the list
    }

    /**
     * @brief Check if the queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool empty() const {
        return queue.empty(); // check if the queue is empty
    }
};

#endif //CHESS_MYPRIORITYQUEUE_H
