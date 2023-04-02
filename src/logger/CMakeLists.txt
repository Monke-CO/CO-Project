add_library(logger-lib STATIC Logger.cpp)
target_include_directories(logger-lib PUBLIC ${PROJECT_SOURCE_DIR}/include/)
