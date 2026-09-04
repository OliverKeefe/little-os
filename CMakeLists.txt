cmake_minimum_required(VERSION 3.31)
project(little_os C)

set(CMAKE_C_STANDARD 11)

add_executable(little_os
        kernel/kernel.c
        main.c
        kernel/kernel.c
        common/common.h)
