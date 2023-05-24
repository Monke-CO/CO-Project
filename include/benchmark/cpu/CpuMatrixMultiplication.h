//
// Created by marc on 5/24/23.
//
#pragma once

#include <vector>
#include <atomic>
namespace bench::Cpu {
    class CpuMatrixMultiplication {
    public:
        CpuMatrixMultiplication();

        void initialize();

        void setMatrixSize(int matrixSize);

        void cancel();

        void setNumThreads(int numThreads);

        void runSingleThreadedBenchmark();
        void runMultiThreadedBenchmark();
        void runAbsoluteBenchmark(bool useMultiThreaded);

        double getResult() const;

    private:
        std::vector<std::vector<int>> matrix1_;
        std::vector<std::vector<int>> matrix2_;

        std::vector<std::vector<int>> matrixMultiplication(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2);

        std::atomic<bool> canceled_;
        int matrixSize;
        int numThreads_;
        double result_;
    };
}

