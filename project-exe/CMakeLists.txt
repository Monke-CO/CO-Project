add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(
        ${PROJECT_NAME}
        logger-lib
        timer-lib
        CPU-lib
)