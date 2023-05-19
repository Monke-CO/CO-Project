#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/gaussLegendreCPU.h"
#include "benchmark/cpu/fixedPointBenchmark.h"

int main() {
    timer::Timer t1;
    t1.start();
    auto *cpu = new BenchMark::Cpu::fixedPointBenchmark();
    cpu->SetSize(100000000000);
    cpu->Warmup();
    cpu->Run();

    Logger::Info(IMPLICIT, "Finished in:", t1.stop());

    return 0;
}