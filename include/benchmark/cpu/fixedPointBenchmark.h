#pragma once

namespace benchmark::cpu {
    class fixedPointBenchmark {
    private:
        int size = 1024;
        bool cancel = false;
    public:
        void warmup();

        void run();

        void setSize(int siz);

        void integerArithmeticTest() const;

        void branchingTest() const;

        void arrayAccessTest() const;

        void getResult();
    };
}