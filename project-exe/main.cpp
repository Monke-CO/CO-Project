#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/whetstoneCpuBenchmark.h"

int main() {
    timer::Timer t1;
    auto *cpu = new benchmark::cpu::whetstoneCpuBenchmark;

    t1.start();
    cpu->initialize(INT32_MAX);
    cpu->warmup();
    Logger::Info(IMPLICIT,"multiThreaded mode");
    cpu->setNrThreads(1);
    cpu->runAbsolute(true);
    Logger::Info(IMPLICIT,"result: " ,cpu->getResult());
    Logger::Info(IMPLICIT, "Finished in:", std::chrono::duration_cast<std::chrono::seconds>(t1.stop()));

    return 0;
}