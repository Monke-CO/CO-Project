add_library(cpu-lib STATIC gaussLegendreCPU.cpp fixedPointBenchmark.cpp whetstoneCpuBenchmark.cpp CpuMatrixMultiplication.cpp)
target_include_directories(cpu-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)



