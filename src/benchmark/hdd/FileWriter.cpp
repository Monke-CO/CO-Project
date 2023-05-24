//
// Created by marc on 5/19/23.
//

#include "benchmark/hdd/FileWriter.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <filesystem>

namespace benchmark {
    namespace hdd {
        const int FileWriter::MIN_BUFFER_SIZE = 1024 * 1; // KB
        const int FileWriter::MAX_BUFFER_SIZE = 1024 * 1024 * 32; // MB
        const long FileWriter::MIN_FILE_SIZE = 1024 * 1024 * 1; // MB
        const long FileWriter::MAX_FILE_SIZE = 1024 * 1024 * 512; // MB

        void Timing::start() {
            start_time = std::chrono::high_resolution_clock::now();
        }

        long long Timing::stop() {
            auto end_time = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        }

        FileWriter::FileWriter() : rand_engine(rd()) {}

        void FileWriter::streamWriteFixedFileSize(const std::string& filePrefix, const std::string& fileSuffix,
                                                  int minIndex, int maxIndex, long fileSize, bool clean) {
            std::cout << "Stream write benchmark with fixed file size\n";
            int currentBufferSize = MIN_BUFFER_SIZE;
            std::string fileName;
            int fileIndex = 0;
            benchScore = 0;

            while (currentBufferSize <= MAX_BUFFER_SIZE && fileIndex <= maxIndex - minIndex) {
                fileName = filePrefix + std::to_string(fileIndex) + fileSuffix;
                writeFile(fileName, currentBufferSize, fileSize, clean);
                currentBufferSize *= 4;
                fileIndex++;
            }

            benchScore /= (maxIndex - minIndex + 1);
            std::size_t partition_pos = filePrefix.find(":\\");
            std::string partition = filePrefix.substr(0, partition_pos);
            std::cout << "File write score on partition " << partition << ": "
                      << std::fixed << std::setprecision(2) << benchScore << " MB/sec\n";
        }

        void FileWriter::streamWriteFixedBufferSize(const std::string& filePrefix, const std::string& fileSuffix,
                                                    int minIndex, int maxIndex, int bufferSize, bool clean) {
            std::cout << "Stream write benchmark with fixed buffer size\n";
            long currentFileSize = MIN_FILE_SIZE;
            int fileIndex = minIndex;

            while (currentFileSize <= MAX_FILE_SIZE && fileIndex <= maxIndex - minIndex) {
                writeFile(filePrefix + std::to_string(fileIndex) + fileSuffix, bufferSize, currentFileSize, clean);
                currentFileSize *= 2;
                fileIndex++;
            }

            benchScore /= (maxIndex - minIndex + 1);
            std::cout << "File write score on partition: "
                      << std::fixed << std::setprecision(2) << benchScore << " MB/sec\n";
        }

        void FileWriter::writeFile(const std::string& fileName, int bufferSize, long fileSize, bool clean) {
            std::filesystem::path folderPath = std::filesystem::path(fileName).parent_path();

            // create folder path to benchmark output
            if (!std::filesystem::is_directory(folderPath))
                std::filesystem::create_directories(folderPath);

            std::ofstream outputStream(fileName, std::ios::binary);

            std::vector<char> buffer(bufferSize);
            int i = 0;
            long toWrite = fileSize / bufferSize;

            timer.start();
            while (i < toWrite) {
                // generate random content to write
                std::generate(buffer.begin(), buffer.end(), [this]() { return rand_engine(); });

                outputStream.write(buffer.data(), bufferSize);
                i++;
            }
            printStats(fileName, fileSize, bufferSize);

            outputStream.close();
            if (clean) {
                std::filesystem::remove(fileName);
            }
        }

        void FileWriter::printStats(const std::string& fileName, long totalBytes, int bufferSize) {
            const long long time = timer.stop();

            double seconds = static_cast<double>(time) / 1000.0;
            double megabytes = static_cast<double>(totalBytes) / (1024 * 1024);
            double rate = megabytes / seconds;
            std::cout << "Done writing " << totalBytes << " bytes to file: " << fileName << " in "
                      << std::fixed << std::setprecision(2) << seconds << " s ("
                      << std::fixed << std::setprecision(2) << rate << " MB/sec)"
                      << " with a buffer size of " << bufferSize / 1024 << " kB\n";

            // actual score is write speed (MB/s)
            benchScore += rate;
        }

    }
}