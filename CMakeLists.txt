# cmake_minimum_required(VERSION <specify CMake version here>)
project(C_stuff C)

set(CMAKE_C_STANDARD 11)

add_executable(cw2q3 src/CW2Q3.c src/hashtable.c src/hashtable.h)