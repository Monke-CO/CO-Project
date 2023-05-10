//
// Created by marc on 4/6/23.
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <thread>
#include "benchmark/cpu/gaussLegendreCPU.h"

namespace benchmark::cpu {
    void gaussLegendreCPU::warmup() {
        gaussLegendreCPU::run();
    }

    void gaussLegendreCPU::run() {
        long double a = 1.0, b = 1.0 / sqrt(2.0), t = 1.0 / 4.0, p = 1.0;
        long double piPrev = 0.0, pi = 0.0;

        int iterations = ceil(log2(this->noDecimals / 14.6)); // Compute number of iterations needed

        for (int i = 0; i < iterations; ++i) {
            if (!this->running) {
                break; //if the cancel command is given we stop iterating
            }
            long double aNext = (a + b) / 2.0;
            long double bNext = sqrt(a * b);
            long double tNext = t - p * pow(a - aNext, 2.0);
            long double pNext = 2.0 * p;

            a = aNext;
            b = bNext;
            t = tNext;
            p = pNext;

            piPrev = pi;
            pi = pow(a + b, 2.0) / (4.0 * t);
            if (pi == piPrev) {
                break; // Stop iterating if no change in pi
            }
        }
    }
    void gaussLegendreCPU::cancel() {
        this->running = false;
    }

    void gaussLegendreCPU::getResult() {
        //for now empty to be implemented when a gui is added
    }

    void gaussLegendreCPU::runMultiThreaded() {
        std::vector<std::thread> threads(this->noThreads);

        for (int t = 0; t < this->noThreads; ++t) {
            threads[t] = std::thread([&]() {
                long double a = 1.0, b = 1.0 / sqrt(2.0), t = 1.0 / 4.0, p = 1.0;
                long double piPrev = 0.0, pi = 0.0;

                int iterations_per_thread = ceil(
                        log2(this->noDecimals / 14.6) /
                        noThreads); // Compute number of iterations per thread

                int start_iteration = t * iterations_per_thread;
                int end_iteration = (t + 1) * iterations_per_thread;
                if (t == noThreads - 1) {
                    end_iteration = ceil(log2(this->noDecimals / 14.6));
                }

                for (int i = start_iteration; i < end_iteration; ++i) {
                    if (!this->running) {
                        break; //if the cancel command is given we stop iterating
                    }

                    long double aNext = (a + b) / 2.0;
                    long double bNext = sqrt(a * b);
                    long double tNext = t - p * pow(a - aNext, 2.0);
                    long double pNext = 2.0 * p;

                    a = aNext;
                    b = bNext;
                    t = tNext;
                    p = pNext;

                    piPrev = pi;
                    pi = pow(a + b, 2.0) / (4.0 * t);
                    if (pi == piPrev) {
                        break; // Stop iterating if no change in pi
                    }
                }
            });
        }
    }
    void gaussLegendreCPU::runAbsolute(bool multithreading){
        if (multithreading) {
            gaussLegendreCPU::runMultiThreaded();
        } else {
            gaussLegendreCPU::run();
        }
    }

    void gaussLegendreCPU::setNoThreads(int noThreads) {
        this->noThreads = noThreads;
    }

    void gaussLegendreCPU::setNoDecimals(int noDecimals) {
        this->noDecimals = noDecimals;
    }

    void gaussLegendreCPU::cleanup() {

    }
    //namespace Cpu
}