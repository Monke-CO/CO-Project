#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>

namespace benchmark {
    namespace hdd {
        class Timing {
            std::chrono::high_resolution_clock::time_point start_time;

        public:
            void start();

            long long stop();
        };

        class FileWriter {
        private:
            static const int MIN_BUFFER_SIZE;
            static const int MAX_BUFFER_SIZE;
            static const long MIN_FILE_SIZE;
            static const long MAX_FILE_SIZE;
            Timing timer;
            std::random_device rd;
            std::mt19937 rand_engine;
            double benchScore;

        public:
            FileWriter();

            void streamWriteFixedFileSize(const std::string &filePrefix, const std::string &fileSuffix,
                                          int minIndex, int maxIndex, long fileSize);

            void streamWriteFixedBufferSize(const std::string &filePrefix, const std::string &fileSuffix,
                                            int minIndex, int maxIndex, int bufferSize);

        private:
            void writeFile(const std::string &fileName, int bufferSize, long fileSize);

            void printStats(const std::string &fileName, long totalBytes, int bufferSize);
        };
    }
}