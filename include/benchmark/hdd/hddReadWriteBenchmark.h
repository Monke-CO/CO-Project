#pragma once

#include <iostream>
#include <fstream>
#include "benchmark/IBenchmark.h"


namespace benchmark::hdd{
    class HDDWriteSpeedBenchmark: public benchmark::IBenchmark{
    private:
        int minIndex;
        int maxIndex;
        std::string prefix;
        std::string suffix;
        double result;
    public:
        double getResult() const;

    public:
        void warmup() override;

        void run() override;

        void run(const std::string& option);

        void cleanup() override;

        void cancel() override;

        void setMinIndex(int minIndex);
        void setMaxIndex(int maxIndex);
        void setPrefix(std::string prefix);
        void setSuffix(std::string suffix);
    };
}