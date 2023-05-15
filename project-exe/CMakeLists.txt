add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/external)

target_link_libraries(${PROJECT_NAME} PUBLIC
        logger-lib
        timer-lib
        cpu-lib
        bignum-lib
)