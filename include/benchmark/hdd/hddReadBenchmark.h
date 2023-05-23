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
        class hddReadBenchmark {
        private:
            const std::string filename = "readableFile.txt";
            bool cancel = false;
            double result;
            int bufferSize;
            std::streampos fileSize;

        public:
            void initialize();

            void warmup();

            void run();

            void Cancel();

            void setBufferSize(int bufferSiz);

            double getResult() const;

            void setFileSize(const std::streampos &fileSiz);
        };
    }

#endif //CO_PROJECT_HDDREADBENCHMARK_H
