#include "benchmark/cpu/fixedPointBenchmark.h"
#include <iostream>

namespace benchmark::cpu {

//        this->arrayAccessTest();
            this->integerArithmeticTest();
            this->branchingTest();
        }
    }

    void fixedPointBenchmark::run() {
//        this->arrayAccessTest();
        this->integerArithmeticTest();
        this->branchingTest();
    }

    void fixedPointBenchmark::setSize(int siz) {
        this->size = siz;
    }

    void fixedPointBenchmark::arrayAccessTest() const {
        int a[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        int b[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        int c[8] = {0, 1, 2, 3, 4, 5, 6, 7};

        for (int i = 0; i < size; i++) {
            c[i%8] = a[b[i%8]];
        }
    }

    void fixedPointBenchmark::branchingTest() const {
        int a[] = {0, 1, 2, 3};
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (j == 1) {
                j = a[2];
            } else {
                j = a[3];
            }
            if (j > 2) {
                j = a[0];
            } else {
                j = a[1];
            }
            if (j < 1) {
                j = a[1];
            } else {
                j = a[0];
            }
        }
    }

    void fixedPointBenchmark::getResult() {
        //to be implemented when gui is added
    }

    void fixedPointBenchmark::integerArithmeticTest() const {
        int a = 0;
        int b = 0;
        int c = 0;
        for(int i = 0; i < size; i++) {
            a = a + 1;
            b = a - 1;
            c = b * 2;
            a = a + c / 2;
        }
    }
}
