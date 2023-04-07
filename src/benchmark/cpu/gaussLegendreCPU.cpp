//
// Created by marc on 4/6/23.
//
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <thread>
#include "benchmark/cpu/gaussLegendreCPU.h"

void gaussLegendreCPU::initialize(int numberOfDecimals) {
    gaussLegendreCPU::noDecimals = numberOfDecimals;
}

void gaussLegendreCPU::warmup() {
    gaussLegendreCPU::run(100);
}

void gaussLegendreCPU::run(int noDigits) {
    long double a = 1.0, b = 1.0 / sqrt(2.0), t = 1.0 / 4.0, p = 1.0;
    long double piPrev = 0.0, pi = 0.0;

    int iterations = ceil(log2(noDigits/14.6)); // Compute number of iterations needed

    for (int i = 0; i < iterations; ++i) {
        if(gaussLegendreCPU::cancel){
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

void gaussLegendreCPU::run() {
    long double a = 1.0, b = 1.0 / sqrt(2.0), t = 1.0 / 4.0, p = 1.0;
    long double piPrev = 0.0, pi = 0.0;

    int iterations = ceil(log2(gaussLegendreCPU::noDecimals / 14.6)); // Compute number of iterations needed

    for (int i = 0; i < iterations; ++i) {
        if(gaussLegendreCPU::cancel){
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

void gaussLegendreCPU::cancelBenchmark() {
    gaussLegendreCPU::cancel = true;
}

void gaussLegendreCPU::getResult() {
    //for now empty to be implemented when a gui is added
}

void gaussLegendreCPU::runMultiThreaded(int noThreads) {
//created a vector that takes threads
//started thread with emplace back
//called a lambda function that captures all variables in the current scope by reference ("[&]")
//and calls the run function

    std::vector<std::thread> ThreadVector;
    for(int i = 0 ; i < noThreads ; i++){
        ThreadVector.emplace_back([&](){gaussLegendreCPU::run();});
    }
    for(auto &t : ThreadVector){
        t.join();
    }
}
