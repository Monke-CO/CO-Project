//
// Created by marc on 4/6/23.
//
#include <iostream>
#include <iomanip>
#include <cmath>
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