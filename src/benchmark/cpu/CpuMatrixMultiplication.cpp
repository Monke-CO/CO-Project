//
// Created by marc on 5/24/23.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "benchmark/cpu/CpuMatrixMultiplication.h"

namespace bench::Cpu{
    CpuMatrixMultiplication::CpuMatrixMultiplication() : canceled_(false), numThreads_(1), result_(0.0) {}

    void CpuMatrixMultiplication::initialize() {
        canceled_.store(false);

        // Create matrix1 and matrix2 with dimensions 2000x2000
        matrix1_.resize(this->matrixSize, std::vector<int>(this->matrixSize, 1));
        matrix2_.resize(this->matrixSize, std::vector<int>(this->matrixSize, 2));

        result_ = 0.0;
    }

    void CpuMatrixMultiplication::cancel() {
        canceled_.store(true);
    }

    void CpuMatrixMultiplication::setNumThreads(int numThreads) {
        numThreads_ = numThreads;
    }

    void CpuMatrixMultiplication::runSingleThreadedBenchmark() {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<int>> result = matrixMultiplication(matrix1_, matrix2_);
        auto end = std::chrono::high_resolution_clock::now();

        if (canceled_.load()) {
            std::cout << "Single-threaded benchmark canceled" << std::endl;
            return;
        }

        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        result_ = matrixSize/static_cast<double>(duration/1000);
        std::cout << "Single-threaded Execution Time: " << duration << "ms" << std::endl;
    }

    void CpuMatrixMultiplication::runMultiThreadedBenchmark() {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        std::vector<std::vector<int>> result(matrix1_.size(), std::vector<int>(matrix2_[0].size(), 0));

        int rows1 = matrix1_.size();
        int cols2 = matrix2_[0].size();
        int rowsPerThread = rows1 / numThreads_;
        int rowsLeft = rows1 % numThreads_;
        int startRow = 0;

        for (int i = 0; i < numThreads_; i++) {
            int endRow = startRow + rowsPerThread + (i < rowsLeft ? 1 : 0);
            threads.emplace_back([this, &result, startRow, endRow]() {
                for (int i = startRow; i < endRow; i++) {
                    if (canceled_.load()) {
                        return;
                    }
                    for (size_t j = 0; j < matrix2_[0].size(); j++) {
                        for (size_t k = 0; k < matrix1_[0].size(); k++) {
                            result[i][j] += matrix1_[i][k] * matrix2_[k][j];
                        }
                    }
                }
            });

            startRow = endRow;
        }

        for (auto& thread : threads) {
            thread.join();
        }

        if (canceled_.load()) {
            std::cout << "Multi-threaded benchmark canceled" << std::endl;
            return;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        result_ =matrixSize/static_cast<double>(duration/1000);
        std::cout << "Multi-threaded Execution Time (" << numThreads_ << " threads): " << duration << "ms" << std::endl;
    }

    void CpuMatrixMultiplication::runAbsoluteBenchmark(bool useMultiThreaded) {
        if (useMultiThreaded) {
            runMultiThreadedBenchmark();
        } else {
            runSingleThreadedBenchmark();
        }
    }

    double CpuMatrixMultiplication::getResult() const {
        return result_;
    }

    std::vector<std::vector<int>> CpuMatrixMultiplication::matrixMultiplication(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
        int rows1 = matrix1.size();
        int cols1 = matrix1[0].size();
        int rows2 = matrix2.size();
        int cols2 = matrix2[0].size();

        std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < cols2; j++) {
                for (int k = 0; k < cols1; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        return result;
    }

    void CpuMatrixMultiplication::setMatrixSize(int matrixSize) {
        CpuMatrixMultiplication::matrixSize = matrixSize;
    }
}