#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    bool running;

public:
    Timer() : running(false) {}

    void startTimer() {
        start = std::chrono::high_resolution_clock::now();
        running = true;
    }

    double stopTimer() {
        if (!running) return 0.0;
        end = std::chrono::high_resolution_clock::now();
        running = false;
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
    }
};

#endif