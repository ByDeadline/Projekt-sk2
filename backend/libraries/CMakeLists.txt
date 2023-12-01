add_library(Rational header/Rational.h cpp/Rational.cpp)

target_include_directories(Rational PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")