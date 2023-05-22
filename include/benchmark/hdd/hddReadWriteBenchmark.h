#pragma once

#include <iostream>
#include <fstream>
#include "benchmark/IBenchmark.h"


namespace benchmark::hdd{
    class HDDWriteSpeedBenchmark: public benchmark::IBenchmark{
        public:
            void warmup() override;

            void run() override;

            void run(const std::string& option);

            void cleanup() override;

            void cancel() override;
        };
    }