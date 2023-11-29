cmake_minimum_required(VERSION 3.16.3)

project(Sk2Backend)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libraries)

add_executable(server main.cpp)
target_link_libraries(server PRIVATE Rational)