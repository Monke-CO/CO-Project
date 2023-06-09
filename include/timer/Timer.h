#pragma once
#include <chrono>

using namespace std::chrono_literals;

namespace timer {
    enum TimerState {
        PAUSED = 0,
        RUNNING,
        STOPPED
    };

    class Timer {
    private:
        TimerState timerState;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::nanoseconds elapsedTime;
        std::chrono::nanoseconds totalTime;
    public:
        Timer(): elapsedTime(0ns), totalTime(0ns), timerState(STOPPED) {}
        void start();

        /**
         * Pauses the timer and sets the TimerState to PAUSED.
         * @returns the time elapsed since the last start/resume of the timer in NANOSECONDS.
         */
        std::chrono::nanoseconds pause();
        void resume();
        std::chrono::nanoseconds stop();
    };
}