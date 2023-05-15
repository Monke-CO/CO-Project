#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/gaussLegendreCPU.h"

int main() {
    timer::Timer t1;
    t1.start();
    auto *cpu = new benchmark::cpu::gaussLegendreCPU();
    cpu->setNoDecimals(10000);
    cpu->setNoThreads(16);
    cpu->runAbsolute(false);

    Logger::Info(IMPLICIT, "Finished in:", t1.stop());

    return 0;
}