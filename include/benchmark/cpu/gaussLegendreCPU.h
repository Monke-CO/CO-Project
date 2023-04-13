//
// Created by marc on 4/6/23.
//

#ifndef CO_PROJECT_GAUSSLEGENDRECPU_H
#define CO_PROJECT_GAUSSLEGENDRECPU_H


class gaussLegendreCPU {
public:
        int noDecimals{};
        int result{};
        bool cancel = false;
        /**
         * it acts as a setter function for the noDecimals variable that decides for how many digits of
         * pi the benchmark will be run
         * @param numberOfDecimals
         */
        void initialize(int numberOfDecimals);
        /**
         * runs the function for a set number of decimals \n \n
         * To be implemented: running the benchmark multiple times
         */
        void warmup();
        /**
        *   Runs the Gauss-Legendre algorithm on a single thread.
        *   The algorithm computes the value of pi with the desired number of decimals
        *   using the Gauss-Legendre algorithm.\n The algorithm runs on a single thread
        *   and iterates until convergence or until the user cancels the computation.
        */
        void runSingleThread();
        /**
         * Runs the Gauss-Legendre algorithm single threaded but it also initializes the function
         * @param noDigits
         */
        void run(int noDigits);
        /**
         * Acts as a switch between multithreading and single threaded operation. \n
         *
         * @param multithreading Uses the multithreading bool to decide if it uses multithreading or not
         * @param noThreads In the case that multithreading is used it decides how many threads will be created
         */
        void runAbsolute(bool multithreading ,int noThreads);
        /**
        *   Runs the Gauss-Legendre algorithm on multiple threads.
        *   The algorithm computes the value of pi with the desired number of decimals
        *   using the Gauss-Legendre algorithm. The algorithm runs on multiple threads,
        *   with each thread computing a subset of the iterations. The number of threads
        *   is specified by the num_threads parameter.
        *   @param num_threads the number of threads to use for the computation
        */
        void runMultiThreaded(int noThreads);
        /**
        *   Cancels the computation of pi.
        *   This function sets the cancel flag to true, which causes the Gauss-Legendre
        *   algorithm to stop iterating on the next iteration. The function can be called
        *   from a separate thread to cancel the computation while it is running.
        */
        void cancelBenchmark();
        /**
         * not yet implemented
         */
        void getResult();
};


#endif //CO_PROJECT_GAUSSLEGENDRECPU_H
