//
// Created by marc on 5/22/23.
//

#include "benchmark/cpu/whetstoneCpuBenchmark.h"
#include <cmath>


namespace benchmark::cpu{
    double whetstoneCpuBenchmark::procedure1(double x, double y, double z) {
        x = y + z;
        return x;
    }

    double whetstoneCpuBenchmark::procedure2(double x, double y, double z){
        x = (y + z) * x;
        return x;
    }

    double whetstoneCpuBenchmark::procedure3(double x, double y, double z){
        x = std::sqrt(std::abs(x + y + z));
        return x;
    }

    double whetstoneCpuBenchmark::procedure4(double x, double y, double z){
        x = std::sqrt(std::abs(x + y + z));
        x = std::sin(x);
        return x;
    }

    void whetstoneCpuBenchmark::run(){
        for (int i = 0; i < itterations; ++i)
        {
            result += procedure1(x, y, z);
            result += procedure2(x, y, z);
            result += procedure3(x, y, z);
            result += procedure4(x, y, z);
        }
    }

    void whetstoneCpuBenchmark::initialize(int itterations){
        this->itterations = itterations;
        this->x = 237.236;
        this->y = 298.976;
        this->z = 353.235;
        this->cancel = false;
    }

    void whetstoneCpuBenchmark::warmup(){
        for (int i = 0; i < itterations/2; ++i)
        {
            result += procedure1(x, y, z);
            result += procedure2(x, y, z);
            result += procedure3(x, y, z);
            result += procedure4(x, y, z);
        }
    }

    double whetstoneCpuBenchmark::getResult(){
        return this->result;
    }
}