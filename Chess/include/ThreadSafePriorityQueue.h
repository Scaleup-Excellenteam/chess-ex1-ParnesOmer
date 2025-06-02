//
// Created by omer on 6/1/2025.
//

#ifndef CHESS_THREADSAFEPRIORITYQUEUE_H
#define CHESS_THREADSAFEPRIORITYQUEUE_H

#include "MyPriorityQueue.h"
#include <mutex>

/**
 * Thread-safe wrapper for MyPriorityQueue.
 * All public methods are guarded with a mutex to ensure safe access by multiple threads.
 * Copying is disabled to prevent accidental sharing of the queue between threads.
 *
 * @tparam T The type of elements in the priority queue.
 */
template <typename T>
class ThreadSafePriorityQueue {
    MyPriorityQueue<T> queue;
    mutable std::mutex mtx;
public:
    ThreadSafePriorityQueue() = default;
    ~ThreadSafePriorityQueue() = default;

    // Disable copy constructor and assignment operator
    ThreadSafePriorityQueue(const ThreadSafePriorityQueue&) = delete;
    ThreadSafePriorityQueue& operator=(const ThreadSafePriorityQueue&) = delete;

    void push(T&& value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
    }

    T pull() {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.pull();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        queue.clear();
    }
};

#endif //CHESS_THREADSAFEPRIORITYQUEUE_H
