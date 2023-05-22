#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/hdd/hddReadWriteBenchmark.h"

int main() {
    timer::Timer t1;
    auto *hdd = new benchmark::hdd::HDDWriteSpeedBenchmark;

    t1.start();
    hdd->run("fb");
    Logger::Info(IMPLICIT, "Finished in:", std::chrono::duration_cast<std::chrono::seconds>(t1.stop()));

    return 0;
}