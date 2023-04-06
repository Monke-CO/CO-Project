add_library(CPU-lib STATIC digitsOfPiBenchmark.cpp)
target_include_directories(CPU-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)
