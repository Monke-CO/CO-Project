#include <thread>
#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/whetstoneCpuBenchmark.h"
#include "benchmark/hdd/HddReadBenchmark.h"
#include "benchmark/cpu/CpuMatrixMultiplication.h"

int main() {
    timer::Timer t1;
    // Create the benchmark object
    auto* benchmark = new Bench::HDD::HddReadBenchmark();
    benchmark->setFileName("readableFile.txt");
    t1.start();
    // Set buffer size to 1MB
    int bufferSize = 4096 ;// 1MB
    benchmark->setBufferSize(bufferSize);

    // Set iterations to 3
    benchmark->setItterations(3);

    // Set file size to 1GB
    long long fileSize = 1024LL * 1024LL * 1024LL * 4LL; // 4GB
    benchmark->initialize(fileSize);

    // Run the benchmark
    benchmark->run();
    Logger::Info(IMPLICIT,"result = ",benchmark->getResult());
    delete benchmark;

    Logger::Info(IMPLICIT, "Finished in:", std::chrono::duration_cast<std::chrono::seconds>(t1.stop()));

    return 0;
}