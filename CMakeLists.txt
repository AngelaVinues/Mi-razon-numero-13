cmake_minimum_required(VERSION 3.26)
project(Account_Manager C)

set(CMAKE_C_STANDARD 11)

add_executable(Account_Manager main.c
        files.h
        usersInfo.c
        usersInfo.h
        files.c)