add_library(hdd-lib STATIC hddReadWriteBenchmark.cpp)
target_include_directories(hdd-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)