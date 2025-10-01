#ifndef THREADPOOL_H
#define THREADPOOL_H

#pragma once
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class Threadpool {
public:
  Threadpool(size_t numThreads = std::thread::hardware_concurrency()) {
    for (size_t i = 0; i < numThreads; ++i) {
      threads.emplace_back([this] {
        while (true) {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this] { return !tasks.empty() || stop; });
            
            if (stop && tasks.empty()) return;

            task = move(tasks.front());
            tasks.pop();
          }

          task();
        }
      });
    }
  }

  ~Threadpool() {
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      stop = true;
    }

    cv.notify_all();

    for (auto& thread : threads) thread.join();
  };

  void enqueue(std::function<void()> task) {
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      tasks.emplace(move(task));
    }
    cv.notify_one();
  }

private:
  std::vector<std::thread> threads;

  std::queue<std::function<void()>> tasks;

  std::mutex queueMutex;

  std::condition_variable cv;

  bool stop = false;
};

#endif