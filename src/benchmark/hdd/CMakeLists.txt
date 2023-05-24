add_library(hdd-lib STATIC hddWriteBenchmark.cpp FileWriter.cpp HddReadBenchmark.cpp)
target_include_directories(hdd-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)