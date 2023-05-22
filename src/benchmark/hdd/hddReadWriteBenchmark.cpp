//
// Created by marc on 5/15/23.
//
#include "benchmark/hdd/FileWriter.h"
#include "benchmark/hdd/hddReadWriteBenchmark.h"

namespace benchmark{
    namespace hdd{

        void HDDWriteSpeedBenchmark::initialize() {
        }

        void HDDWriteSpeedBenchmark::warmUp() {
        }

        void HDDWriteSpeedBenchmark::run() {
            throw std::runtime_error("Method not implemented. Use run(Object) instead");
        }

        void HDDWriteSpeedBenchmark::run(const std::string& option, bool clean) {
            FileWriter writer;
            std::string prefix = "data-files/cotestlab";
            std::string suffix = ".dat";
            int minIndex = 0;
            int maxIndex = 8;
            long fileSize = 1024 * 1024 * 1024; // 256, 512 MB, 1GB
            int bufferSize = 1024 * 4; // 4 KB

            try {
                if (option == "fs")
                    writer.streamWriteFixedFileSize(prefix, suffix, minIndex, maxIndex, fileSize, clean);
                else if (option == "fb")
                    writer.streamWriteFixedBufferSize(prefix, suffix, minIndex, maxIndex, bufferSize, clean);
                else
                    throw std::invalid_argument("Argument " + option + " is undefined");
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        void HDDWriteSpeedBenchmark::clean() {
            // Clean temp files here
            std::string prefix = "~/cotestlab";
            std::string suffix = ".dat";
            int minIndex = 0;
            int maxIndex = 8;
            for (int i = minIndex; i <= maxIndex; ++i) {
                std::string filename = prefix + std::to_string(i) + suffix;
                std::remove(filename.c_str());
            }

        }

        void HDDWriteSpeedBenchmark::cancel() {

        }

        std::string HDDWriteSpeedBenchmark::getResult() {
            return ""; // or MBps
        }
    }
}