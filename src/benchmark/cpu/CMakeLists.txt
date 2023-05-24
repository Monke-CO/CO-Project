add_library(cpu-lib STATIC whetstoneCpuBenchmark.cpp CpuMatrixMultiplication.cpp)
target_include_directories(cpu-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)



