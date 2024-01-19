cmake_minimum_required(VERSION 3.16.3)

project(Sk2Backend)
set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp)

include_directories(libraries/header)
file(GLOB LIB_SOURCES "libraries/cpp/*.cpp")
target_sources(server PRIVATE ${LIB_SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)