#include "benchmark/hdd/FileWriter.h"
#include "benchmark/hdd/hddWriteBenchmark.h"

namespace benchmark::hdd{
    void HDDWriteSpeedBenchmark::run() {
        throw std::runtime_error("Method not implemented. Use run(Object) instead");
    }

    void HDDWriteSpeedBenchmark::run(const std::string& option) {
        FileWriter writer;
        long fileSize = 1024 * 1024 * 1024; // 256, 512 MB, 1GB
        int bufferSize = 1024 * 4; // 4 KB

        try {
            if (option == "fs")
              result = writer.streamWriteFixedFileSize(this->prefix, this->suffix, this->minIndex, this->maxIndex, fileSize);
            else if (option == "fb")
               result = writer.streamWriteFixedBufferSize(this->prefix, this->suffix, this->minIndex, this->maxIndex, bufferSize);
            else
                throw std::invalid_argument("Argument " + option + " is undefined");
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void HDDWriteSpeedBenchmark::cleanup() {
        for (int i = minIndex; i <= maxIndex; ++i) {
            std::string filename = this->prefix + std::to_string(i) + this->suffix;
            std::remove(filename.c_str());
        }

    }

    void HDDWriteSpeedBenchmark::cancel() {

    }

    void HDDWriteSpeedBenchmark::warmup() {

    }

    void HDDWriteSpeedBenchmark::setMinIndex(int value) {
        this->minIndex = value;
    }

    void HDDWriteSpeedBenchmark::setMaxIndex(int value) {
        this->maxIndex = value;
    }

    void HDDWriteSpeedBenchmark::setPrefix(std::string value) {
        this->prefix = value;
    }

    void HDDWriteSpeedBenchmark::setSuffix(std::string value) {
        this->suffix = value;
    }

    double HDDWriteSpeedBenchmark::getResult() const {
        return result;
    }
}