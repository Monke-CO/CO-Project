#include <thread>
#include "logger/Logger.h"
#include "timer/Timer.h"
#include "benchmark/cpu/whetstoneCpuBenchmark.h"
#include "benchmark/hdd/hddReadBenchmark.h"
#include "benchmark/cpu/CpuMatrixMultiplication.h"

int main() {
    timer::Timer t1;
    // Create the benchmark object
    auto* cpu = new bench::Cpu::CpuMatrixMultiplication();
      cpu->setMatrixSize(2000);
      t1.start();
//    // Initialize the matrices with dimensions 2000x2000
//    cpu.initialize();
//
//    // Run single-threaded benchmark
//    cpu.runAbsoluteBenchmark(false);
//    std::cout << "Result: " << cpu.getResult() << std::endl;
//
//    // Set the number of threads and run multi-threaded benchmark
//    cpu.setNumThreads(2);
//    cpu.runAbsoluteBenchmark(true);
//    std::cout << "Result: " << cpu.getResult() << std::endl;
//
//    cpu.setNumThreads(4);
//    cpu.runAbsoluteBenchmark(true);
//    std::cout << "Result: " << cpu.getResult() << std::endl;
//
//    cpu.setNumThreads(8);
//    cpu.runAbsoluteBenchmark(true);
//    std::cout << "Result: " << cpu.getResult() << std::endl;
//
//    // Delay for 2 seconds
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//
    // Initialize and run the benchmarks again
    cpu->initialize();
    cpu->runAbsoluteBenchmark(false);
    std::cout << "Result: " << cpu->getResult() << std::endl;

    cpu->setNumThreads(5);
    cpu->runAbsoluteBenchmark(true);
    std::cout << "Result: " << cpu->getResult() << std::endl;
//
//    // Cancel the benchmarks
//    cpu.cancel();
//    cpu.runAbsoluteBenchmark(false);
//    std::cout << "Result: " << cpu.getResult() << std::endl;
//
//    cpu.setNumThreads(8);
//    cpu.runAbsoluteBenchmark(true);
//    std::cout << "Result: " << cpu.getResult() << std::endl;

    Logger::Info(IMPLICIT, "Finished in:", std::chrono::duration_cast<std::chrono::seconds>(t1.stop()));

    return 0;
}