add_executable(${PROJECT_NAME} main.cpp ../include/benchmark/IBenchmark.h)
target_link_libraries(
        ${PROJECT_NAME}
        logger-lib
        timer-lib
)