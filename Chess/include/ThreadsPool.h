//
// Created by omer on 5/27/2025.
//

#ifndef CHESS_THREADSPOOL_H
#define CHESS_THREADSPOOL_H
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <functional>
#include <condition_variable>
#include <future>
#include "MyPriorityQueue.h"
#include "Move.h"

/**
 * @brief Simple thread pool to run tasks in parallel.
 *
 * Thread safety: all public methods are thread-safe.
 * The pool is non-copyable and should be destructed to join all threads.
 */
class ThreadsPool {
    std::vector<std::thread> workers;                     // Worker threads
    std::queue<std::function<void()>> tasks;              // Task queue
    std::mutex queue_mutex;                               // Protects the queue
    std::condition_variable condition;                    // Signals worker threads
    bool stop;                                            // Stop flag

public:
    /**
     * @brief Start the thread pool.
     * @param numThreads Number of worker threads.
     * Each worker waits for tasks and processes them as they arrive.
     * The pool is ready immediately after construction.
     */
    explicit ThreadsPool(int numThreads) : stop(false){
        for (int i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                for(;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // Wait until there's a task or the pool is stopping
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        // Exit if no more tasks and we're stopping
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    // Protect the pool from exceptions thrown in user tasks
                    try {
                        task(); // Execute the task
                    } catch (const std::exception &e) {
                        std::cerr << "Exception in thread pool worker: " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "Unknown exception in thread pool worker." << std::endl;
                    }
                }
            });
        }
    }

    /**
     * @brief Thread-safe wrapper for MyPriorityQueue using std::mutex.
     *
     * Allows safe concurrent access from multiple threads.
     * Copy and assignment are disabled.
     *
     * @tparam T The element type. Must be movable into the underlying queue.
     */
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result_t<F, Args...>>
    {
        using return_type = typename std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (stop)
                throw std::runtime_error("enqueue on stopped ThreadsPool");
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    /**
     * @brief Gracefully stop the pool and join all threads.
     */
    ~ThreadsPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
            worker.join();
    }

    // Disallow copying/moving
    ThreadsPool(const ThreadsPool&) = delete;
    ThreadsPool& operator=(const ThreadsPool&) = delete;
};

#endif //CHESS_THREADSPOOL_H
