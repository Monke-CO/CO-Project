//
// Created by marc on 4/6/23.
//

#ifndef CO_PROJECT_GAUSSLEGENDRECPU_H
#define CO_PROJECT_GAUSSLEGENDRECPU_H

namespace BenchMark {
    namespace Cpu {
        class gaussLegendreCPU {
        public:
            int noDecimals;
            int result;
            int noThreads;
            bool cancel = false;

            void initialize(int numberOfDecimals, int noThreads);

            void warmup();

            void runSingleThread();

            void run(int noDigits);

            void runAbsolute(bool multithreading);

            void runMultiThreaded(int noThreads);

            void cancelBenchmark();

            void getResult();
        };
        //namespace cpu
    }
    //namespace benchmark
}
#endif //CO_PROJECT_GAUSSLEGENDRECPU_H