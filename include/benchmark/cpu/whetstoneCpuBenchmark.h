//
// Created by marc on 5/22/23.
//

#ifndef CO_PROJECT_WHETSTONECPUBENCHMARK_H
#define CO_PROJECT_WHETSTONECPUBENCHMARK_H
#include <cmath>
namespace benchmark::cpu {
        class whetstoneCpuBenchmark {
        private:
            int itterations;
            double x, y, z;
            bool cancel;
            double result;
            int nrThreads;
            bool multiThreading;

        public:
            double procedure1(double x, double y, double z);

            double procedure2(double x, double y, double z);

            double procedure3(double x, double y, double z);

            double procedure4(double x, double y, double z);

            void run();

            void runMultiThreaded();

            void runAbsolute(bool multiThreading);

            void initialize(int itterations);

            void setNrThreads(int nrThreads);

            void warmup();

            double getResult();
        };
}
#endif //CO_PROJECT_WHETSTONECPUBENCHMARK_H
