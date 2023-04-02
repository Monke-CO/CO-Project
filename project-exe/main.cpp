#include "logger/Logger.h"
#include "timer/Timer.h"

int main() {
    timer::Timer t1;
    t1.start();
    for (long long i = 0; i < 1'000'000'000; i++) {
        if (i % 1'000'000 == 0) {
            Logger::Info(IMPLICIT, "Lap ", i/1'000'000, "finished in:", t1.pause());
            t1.resume();
        }
    }
    Logger::Info(IMPLICIT, "Finished in:", t1.stop());

    return 0;
}