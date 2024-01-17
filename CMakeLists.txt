cmake_minimum_required(VERSION 3.27)
project(c-embedded C)

set(CMAKE_C_STANDARD 11)

add_executable(math math.c)
add_executable(strings strings.c)
add_executable(list list.c)
add_executable(task2 task2.c)
add_executable(task1 task1.c)
