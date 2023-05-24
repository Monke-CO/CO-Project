//
// Created by marc on 5/23/23.
//

#include "benchmark/hdd/HddReadBenchmark.h"
namespace Bench::HDD{
    HddReadBenchmark::HddReadBenchmark() : isCancelled(false), bufferSize(0), fileSize(0) {}
    void HddReadBenchmark::initialize(long long fileSiz)
    {
        this->fileSize = fileSiz;
    }

    void HddReadBenchmark::run()
    {
        for(int l = 0 ; l < itterations ; l++){
            generateFile();
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

            double transferRate;
            std::string transferRateUnit;

            if (duration.count() < 1.0)
            {
                transferRate = totalBytesRead / duration.count()/(1024.0*1024.0);
                transferRateUnit = "B/s";
            }
            else
            {
                transferRate = (totalBytesRead / duration.count()) / (1024.0 * 1024.0);
                transferRateUnit = "MB/s";
            }

            std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
            std::cout << "Transfer rate: " << transferRate << " " << transferRateUnit << std::endl;
            result+=transferRate;
            // Delete the file
            std::remove(this->fileName.c_str());
        }

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
        const int bufferSiz = 4 * 1024 * 1024; // 4MB buffer size
        char* buffer = new char[bufferSiz];

        std::ofstream file(this->fileName, std::ios::binary);

        long long bytesWritten = 0;
        while (bytesWritten < this->fileSize)
        {
            file.write(buffer, bufferSiz);
            bytesWritten += bufferSiz;
        }

        file.close();

        delete[] buffer;
    }

    void HddReadBenchmark::setItterations(int iterations) {
        HddReadBenchmark::itterations = iterations;
    }

    double HddReadBenchmark::getResult() {
        result /= itterations;
        return result;
    }

}