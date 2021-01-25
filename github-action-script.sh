#!/bin/bash

echo "I will first build the project"
mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake --build .
echo "I will now launch the unit test command"
cd tests/bin/ && ./unit_tests_server
echo "Test were launched"