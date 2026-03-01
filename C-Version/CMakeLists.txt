cmake_minimum_required(VERSION 4.1)
project(C_Version C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Version main.c
        args.c
        bmp.c
        bmp.h
        args.h)
