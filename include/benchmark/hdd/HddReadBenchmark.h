//
// Created by marc on 5/23/23.
//
#pragma once
#ifndef CO_PROJECT_HDDREADBENCHMARK_H
#define CO_PROJECT_HDDREADBENCHMARK_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>

namespace Bench::HDD {

    class HddReadBenchmark {
    private:
        bool isCancelled;
        std::string fileName;
        long long fileSize;
        int bufferSize;
        int itterations;
        double result;

    public:
        HddReadBenchmark();
        void initialize(long long fileSiz);
        void run();
        void setBufferSize(int bufferSize);

        double getResult();

        void setFileName(const std::string& fileName);
        void cancel();
        void setItterations(int iterations);

    private:
        void generateFile();
    };

}

#endif //CO_PROJECT_HDDREADBENCHMARK_H
