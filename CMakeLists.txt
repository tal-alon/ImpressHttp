cmake_minimum_required(VERSION 3.20)
project(ImpressHttp)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        ImpressHttp src/main.cpp
        src/request.cpp src/request.h
        src/method.cpp src/method.h
        )
