//
// Created by marc on 5/23/23.
//

#include "benchmark/hdd/HddReadBenchmark.h"
namespace Bench::HDD{
    HddReadBenchmark::HddReadBenchmark() : isCancelled(false), bufferSize(0), fileSize(0) {}
    void HddReadBenchmark::initialize(long long fileSiz)
    {
        this->fileSize = fileSiz;
        generateFile();
    }

    void HddReadBenchmark::run()
    {
        std::ifstream file(this->fileName, std::ios::binary);

        long long totalBytesRead = 0;
        char* buffer = new char[this->bufferSize];

        auto startTime = std::chrono::high_resolution_clock::now();

        while (file && !this->isCancelled)
        {
            file.read(buffer, this->bufferSize);
            totalBytesRead += file.gcount();
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

        file.close();

        delete[] buffer;

        std::cout << "Total bytes read: " << totalBytesRead << " bytes" << std::endl;

        if (duration.count() < 1.0)
        {
            std::cout << "Elapsed time: " << duration.count() * 1000.0 << " milliseconds" << std::endl;
            std::cout << "Transfer rate: " << (totalBytesRead / (1024.0 * 1024.0 * 1024.0)) / duration.count() << " GB/s" << std::endl;
        }
        else
        {
            std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
            std::cout << "Transfer rate: " << (totalBytesRead / (1024.0 * 1024.0)) / duration.count() << " MB/s" << std::endl;
        }

        // Delete the file
        std::remove(this->fileName.c_str());
    }

    void HddReadBenchmark::setBufferSize(int bufferSize)
    {
        this->bufferSize = bufferSize;
    }

    void HddReadBenchmark::setFileName(const std::string& fileName)
    {
        this->fileName = fileName;
    }

    void HddReadBenchmark::cancel()
    {
        this->isCancelled = true;
    }

    void HddReadBenchmark::generateFile()
    {
        const int bufferSize = 4 * 1024 * 1024; // 4MB buffer size
        char* buffer = new char[bufferSize];

        std::ofstream file(this->fileName, std::ios::binary);

        long long bytesWritten = 0;
        while (bytesWritten < this->fileSize)
        {
            file.write(buffer, bufferSize);
            bytesWritten += bufferSize;
        }

        file.close();

        delete[] buffer;
    }

}