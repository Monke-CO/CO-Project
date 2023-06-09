//
// Created by marc on 5/22/23.
//

#include "benchmark/cpu/whetstoneCpuBenchmark.h"
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>


namespace benchmark::cpu{
    double whetstoneCpuBenchmark::procedure1(double x, double y, double z) {
        x = y + z;
        return x;
    }

    double whetstoneCpuBenchmark::procedure2(double x, double y, double z){
        x = (y + z) * x;
        return x;
    }

    double whetstoneCpuBenchmark::procedure3(double x, double y, double z){
        x = std::sqrt(std::abs(x + y + z));
        return x;
    }

    double whetstoneCpuBenchmark::procedure4(double x, double y, double z){
        x = std::sqrt(std::abs(x + y + z));
        x = std::sin(x);
        return x;
    }

    void whetstoneCpuBenchmark::run(){
        for (int i = 0; i < iterations; ++i)
        {
            result += procedure1(x, y, z);
            result += procedure2(x, y, z);
            result += procedure3(x, y, z);
            result += procedure4(x, y, z);
        }
    }

    void whetstoneCpuBenchmark::runMultiThreaded() {
        // Vector to store the threads
        std::vector<std::thread> threads;

        // Create a lambda function to execute the benchmark for a given range of iterations
        auto benchmarkFunc = [&](int start, int end) {
            double threadResult = 0.0;
            for (int i = start; i < end; ++i)
            {
                threadResult += procedure1(x, y, z);
                threadResult += procedure2(x, y, z);
                threadResult += procedure3(x, y, z);
                threadResult += procedure4(x, y, z);
            }

            // Accumulate the thread result to the shared result
            {
                std::lock_guard<std::mutex> lock(resultMutex);
                result += threadResult;
            }
        };

        // Calculate the workload for each thread
        int workload = iterations / nrThreads;
        int remainingWorkload = iterations % nrThreads;

        // Launch the threads
        for (int i = 0; i < nrThreads; ++i)
        {
            int start = i * workload;
            int end = start + workload;
            // Distribute remaining workload evenly among threads
            if (i == nrThreads - 1)
                end += remainingWorkload;

            threads.emplace_back(benchmarkFunc, start, end);
        }

        // Wait for all threads to finish
        for (auto& thread : threads)
        {
            if (thread.joinable())
                thread.join();
        }
    }

    void whetstoneCpuBenchmark::runAbsolute(bool multiThreading) {
        this->t2.start();
        if(multiThreading){
            runMultiThreaded();
        }
        else{
            run();
        }
        this->time = this->t2.stop();
    }

    void whetstoneCpuBenchmark::initialize(int iterations){
        this->iterations = iterations;
        this->x = 2.236;
        this->y = 9.976;
        this->z = 3.235;
        this->cancel = false;
    }

    void whetstoneCpuBenchmark::warmup(){
        for (int i = 0; i < iterations / 2; ++i)
        {
            procedure1(x, y, z);
            procedure2(x, y, z);
            procedure3(x, y, z);
            procedure4(x, y, z);
        }
    }

    double whetstoneCpuBenchmark::getResult(){
        result = (iterations) / std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
        result /= 1000;
        return this->result;
    }

    void whetstoneCpuBenchmark::setNrThreads(int nrThreads) {
        this->nrThreads = nrThreads;
    }
}