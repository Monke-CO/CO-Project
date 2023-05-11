//
// Created by marc on 5/10/23.
//

#ifndef CO_PROJECT_FIXEDPOINTBENCHMARK_H
#define CO_PROJECT_FIXEDPOINTBENCHMARK_H

namespace BenchMark {
    namespace Cpu {
        class fixedPointBenchmark {
        private:
            int size;
            bool cancel;
        public:
            void Cancel(bool cance);

            void Warmup();

            void Run();

            void SetSize(int siz);

            void IntegerArithmeticTest();

            void BranchingTest();

            void ArrayAccessTest();

            void GetResult();
        };
        //namespace cpu
    }
    //namespace benchmark
}


#endif //CO_PROJECT_FIXEDPOINTBENCHMARK_H
