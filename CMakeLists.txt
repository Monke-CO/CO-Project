cmake_minimum_required(VERSION 3.25)
project("CO-Project")
set(CMAKE_CXX_STANDARD 20) # Use C++ 20 as a standard (this is required by the logger library)

add_subdirectory(src)
add_subdirectory(project-exe)
