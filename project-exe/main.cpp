#include "logger/Logger.h"
#include "timer/Timer.h"
#include "CPU/gaussLegendreCpu.h"
#include "../include/benchmark/CPU/gaussLegendreCpu.h"

int main() {
    timer::Timer t1;
    t1.start();
    auto *cpu = new gaussLegendreCpu();
    cpu->initialize(1000);
    cpu->warmup();
    cpu->run();

    Logger::Info(IMPLICIT, "Finished in:", t1.stop());

    return 0;
}