#!/bin/bash
mkdir -p build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
make -C build