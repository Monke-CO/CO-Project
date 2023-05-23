//
// Created by marc on 5/15/23.
//

#ifndef CO_PROJECT_HDDWRITEBENCHMARK_H
#define CO_PROJECT_HDDWRITEBENCHMARK_H

#include <iostream>
#include <fstream>


namespace benchmark{
    namespace hdd{
        class HDDWriteSpeedBenchmark {
        public:
            void initialize();

            void warmUp();

            void run();

            void run(const std::string& option, bool clean);

            void clean();

            void cancel();

            std::string getResult();
        };
    }
}
#endif //CO_PROJECT_HDDWRITEBENCHMARK_H
