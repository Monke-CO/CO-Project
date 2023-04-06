#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/gaussLegendreCPU.h"

int main() {
    timer::Timer t1;
    t1.start();
    auto *cpu = new gaussLegendreCPU();
    cpu->initialize(1000);
    cpu->warmup();
    cpu->run();

    Logger::Info(IMPLICIT, "Finished in:", t1.stop());

    return 0;
}