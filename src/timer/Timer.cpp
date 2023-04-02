#include "timer/Timer.h"
#include "logger/Logger.h"
#include <chrono>

using namespace std::chrono_literals;

namespace timer {
    void Timer::start() {
        this->totalTime = 0ns;
        this->startTime = std::chrono::high_resolution_clock::now();
        this->timerState = RUNNING;
    }

    void Timer::resume() {
        if (this->timerState == PAUSED) {
            this->startTime = std::chrono::high_resolution_clock::now();
            this->timerState = RUNNING;
        } else if (this->timerState == RUNNING) {
            Logger::Warn(IMPLICIT, "The timer is already running!");
        } else {
            Logger::Warn(IMPLICIT, "Cannot resume a stopped timer!");
        }
    }

    /**
     * Pauses the timer and sets the TimerState to PAUSED.
     * @returns the time elapsed since the last start/resume of the timer in NANOSECONDS.
     */
    std::chrono::nanoseconds Timer::pause() {
        if (this->timerState == RUNNING)
        {
            this->timerState = PAUSED;

            auto endTime = std::chrono::high_resolution_clock::now();
            this->elapsedTime = endTime - this->startTime;

            this->totalTime += this->elapsedTime;
        } else {
            Logger::Warn(IMPLICIT, "The timer is already paused!");

            return 0ns;
        }

        return std::chrono::duration_cast<std::chrono::nanoseconds>(this->elapsedTime);
    }

    std::chrono::nanoseconds Timer::stop() {
        if (this->timerState == RUNNING) {
            this->timerState = STOPPED;

            auto endTime = std::chrono::high_resolution_clock::now();
            this->elapsedTime = endTime - this->startTime;

            this->totalTime += this->elapsedTime;
        } else if (this->timerState == STOPPED){
            Logger::Warn(IMPLICIT, "The timer is already stopped!");
        }

        return this->totalTime;
    }

} // namespace timer
