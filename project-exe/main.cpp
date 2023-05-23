#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/whetstoneCpuBenchmark.h"
#include "benchmark/hdd/hddReadBenchmark.h"

int main() {
    timer::Timer t1;
    auto *hdd = new Bench::HDD::hddReadBenchmark;
    t1.start();
    hdd->setFileSize(1024LL*1024LL*1024LL * 4);
    hdd->setBufferSize(4026);
    hdd->initialize();
//    hdd->warmup();
    hdd->run();

//    t1.start();
//    cpu->initialize(INT32_MAX);
//    cpu->warmup();
//    cpu->setNrThreads(5);
//    cpu->runAbsolute(true);
    Logger::Info(IMPLICIT, "Finished in:", std::chrono::duration_cast<std::chrono::seconds>(t1.stop()));

    return 0;
}