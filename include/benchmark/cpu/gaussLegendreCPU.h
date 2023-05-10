//
// Created by marc on 4/6/23.
//
#pragma once

#include "benchmark/IBenchmark.h"

namespace benchmark::cpu {
    class gaussLegendreCPU : public IBenchmark {
    private:
        int noDecimals;
        int result;
        int noThreads;
        bool running = true;

    public:

        void warmup() override;
        void run() override;
        void runAbsolute(bool multithreading);
        void runMultiThreaded();

        void setNoThreads(int);
        void setNoDecimals(int);

        void cancel() override;
        void cleanup() override;

        void getResult();
    };
}