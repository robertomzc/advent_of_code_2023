cmake_minimum_required(VERSION 3.27)
project(advent_of_code_2023)

set(CMAKE_CXX_STANDARD 17)

add_executable(days/day1/day1Main.cpp
        common/text_file.cpp
        common/text_file.h
        common/text_file.cpp
        days/day2/day2Main.cpp
        common/pstring.cpp
        common/pstring.h)
