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
        for (int i = 0; i < itterations; ++i)
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

        // Calculate the workload for each thread
        int workload = itterations / nrThreads;
        int remainingWorkload = itterations % nrThreads;

        // Launch the threads
        for (int i = 0; i < nrThreads; ++i)
        {
            int start = i * workload;
            int end = start + workload;
            double threadResult = 0.0;
            // Distribute remaining workload evenly among threads
            if (i == nrThreads - 1)
                end += remainingWorkload;

            threads.emplace_back([&]() {
                for (int i = start; i < end; ++i)
                {
                    threadResult += procedure1(x, y, z);
                    threadResult += procedure2(x, y, z);
                    threadResult += procedure3(x, y, z);
                    threadResult += procedure4(x, y, z);
                }

                // Accumulate the thread result to the shared result
                std::lock_guard<std::mutex> lock(resultMutex);
                result += threadResult;
            });
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

    void whetstoneCpuBenchmark::initialize(int itterations){
        this->itterations = itterations;
        this->x = 2.236;
        this->y = 9.976;
        this->z = 3.235;
        this->cancel = false;
    }

    void whetstoneCpuBenchmark::warmup(){
        for (int i = 0; i < itterations/2; ++i)
        {
            procedure1(x, y, z);
            procedure2(x, y, z);
            procedure3(x, y, z);
            procedure4(x, y, z);
        }
    }

    double whetstoneCpuBenchmark::getResult(){
        result /=(itterations);
        result =result / std::chrono::duration_cast<std::chrono::seconds>(time).count();
        result *= 100;
        return this->result;
    }

    void whetstoneCpuBenchmark::setNrThreads(int nrThreads) {
        this->nrThreads = nrThreads;
    }
}