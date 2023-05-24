//
// Created by marc on 5/23/23.
//

#include "benchmark/hdd/hddReadBenchmark.h"
namespace Bench::HDD{
    void hddReadBenchmark::initialize() {
//        this->fileSize = static_cast<std::streampos>(this->fileSize * 1024 * 1024);
        std::ofstream file(filename, std::ios::binary | std::ios::out);
        if (!file) {
            std::cerr << "Failed to create file: " << filename << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        double i = 0.0;

        char buffer[this->bufferSize];
        long long bytesRemaining = fileSize;

        while (bytesRemaining > 0) {
            int bytesToWrite = std::min(static_cast<long long>(this->bufferSize), bytesRemaining);

            for (int i = 0; i < bytesToWrite; ++i) {
                buffer[i] = static_cast<char>(dis(gen));
            }

            file.write(buffer, bytesToWrite);
            bytesRemaining -= bytesToWrite;
        }


        file.close();
    }

    void hddReadBenchmark::warmup() {
            this->run();
    }

    void hddReadBenchmark::run() {
        char* buffer = new char[bufferSize];

        std::ifstream file(this->filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << this->filename << std::endl;
            delete[] buffer;
            return;
        }

        auto startTime = std::chrono::high_resolution_clock::now();

        while (!cancel && !file.eof()) {
            file.read(buffer, bufferSize);
            // Reading in progress...
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds >(endTime - startTime).count();

//        fileSize = file.tellg();
        std::cout<< duration/1000;
        double readSpeed = 0;
        if (duration/1000 >1) {
            readSpeed = static_cast<double > (this->fileSize) / (duration / 1000) / (1024 * 1024);
        }
        else{
            readSpeed = (static_cast<double > (this->fileSize)*10) / (duration/ 100) / (1024 * 1024);
        }
        this->result = readSpeed;
        std::cout << "Read speed: " << readSpeed << " MB/s" << std::endl;

        file.close();
        delete[] buffer;

        std::remove(filename.c_str()); // Delete the file
    }

    void hddReadBenchmark::setFileSize(const std::streampos &fileSiz) {
        hddReadBenchmark::fileSize = fileSiz;
    }

    void hddReadBenchmark::Cancel() {
        this->cancel = true;
    }

    double hddReadBenchmark::getResult() const {
        return result;
    }

    void hddReadBenchmark::setBufferSize(int bufferSiz) {
        hddReadBenchmark::bufferSize = bufferSiz;
    }
}