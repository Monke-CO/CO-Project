//
// Created by marc on 5/11/23.
//

#include "benchmark/cpu/fixedPointBenchmark.h"

namespace BenchMark::Cpu {
            void fixedPointBenchmark::Cancel(bool cance) {
                this->cancel = cance;
            };

            void fixedPointBenchmark::Warmup() {
                ArrayAccessTest();
                IntegerArithmeticTest();
                BranchingTest();
            }

            void fixedPointBenchmark::Run() {
                ArrayAccessTest();
                IntegerArithmeticTest();
                BranchingTest();
            }

            void fixedPointBenchmark::SetSize(int siz) {
                this->size = siz;
            }

            void fixedPointBenchmark::ArrayAccessTest() {
                int a[size];
                int b[size];
                int c[size];

                for (int i = 0; i < size; i++) {
                    if(cancel){
                        break;
                    }
                    c[i] = a[b[i]];
                }
            }

            void fixedPointBenchmark::BranchingTest() {
                int a[] = {0, 1, 2, 3};
                int j = 0;
                for (int i = 0; i < size; i++) {
                    if(cancel){
                        break;
                    }
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

            void fixedPointBenchmark::GetResult() {
                //to be implemented when gui is added
            }

            void fixedPointBenchmark::IntegerArithmeticTest() {
                int a = 0;
                int b = 0;
                int c = 0;
                for(int i = 0; i < size; i++) {
                    if(cancel){
                        break;
                    }
                    a = a + 1;
                    b = a - 1;
                    c = b * 2;
                    a = a + c / 2;
                }
            }
        //namespace cpu
    }

