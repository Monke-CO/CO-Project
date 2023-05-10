//
// Created by alex on 21.04.2023.
//
#pragma once

namespace benchmark {
    class IBenchmark {
    public:
        virtual void run() = 0;
        virtual void warmup() = 0;
        virtual void cleanup() = 0;
        virtual void cancel() = 0;
    };
}