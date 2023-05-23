//
// Created by marc on 5/23/23.
//

#include "benchmark/hdd/hddReadBenchmark.h"
namespace Bench::HDD{
    void hddReadBenchmark::initialize() {

        std::ofstream file(filename, std::ios::binary | std::ios::out);
        if (!file) {
            std::cerr << "Failed to create file: " << filename << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        std::streampos i = 0;
        while (i < this->fileSize) {
            char randomChar = static_cast<char>(dis(gen));
            file.write(&randomChar, sizeof(char));
            i += sizeof(char);
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

        while (file.read(buffer, bufferSize)) {
            if (cancel){
                break;
            }
            // Reading in progress...
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds >(endTime - startTime).count();

//        fileSize = file.tellg();
        long readSpeed = (this->fileSize/1024) / (duration);

        std::cout << "Read speed: " << readSpeed << " MB/s" << std::endl;

        file.close();
        delete[] buffer;

        std::remove(filename.c_str()); // Delete the file
    }

    void hddReadBenchmark::setFileSize(const std::streampos &fileSize) {
        hddReadBenchmark::fileSize = fileSize;
    }

    void hddReadBenchmark::Cancel() {
        this->cancel = true;
    }

    double hddReadBenchmark::getResult() const {
        return result;
    }

    void hddReadBenchmark::setBufferSize(int bufferSize) {
        hddReadBenchmark::bufferSize = bufferSize;
    }
}