//
// Created by marc on 4/6/23.
//

#ifndef CO_PROJECT_GAUSSLEGENDRECPU_H
#define CO_PROJECT_GAUSSLEGENDRECPU_H


class gaussLegendreCpu {
public:
        int noDecimals;
        int result;
        bool cancel = false;
        void initialize(int numberOfDecimals);
        void warmup();
        void run();
        void run(int noDigits);
        void cancelBenchmark();
        void getResult();
};


#endif //CO_PROJECT_GAUSSLEGENDRECPU_H
