//
// Created by alex on 21.04.2023.
//
#pragma once
namespace Benchmark {
    class IBenchmark {
    public:
        virtual ~IBenchmark() = default;

        virtual void run() = 0;

        virtual void initialize() = 0;

        virtual void cleanup() = 0;

        virtual void cancel() = 0;
    };
}