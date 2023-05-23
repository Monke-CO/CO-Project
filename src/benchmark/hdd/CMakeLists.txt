add_library(hdd-lib STATIC hddWriteBenchmark.cpp FileWriter.cpp hddReadBenchmark.cpp)
target_include_directories(hdd-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)