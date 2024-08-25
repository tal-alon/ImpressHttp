cmake_minimum_required(VERSION 3.20)
project(ImpressHttp)

set(CMAKE_CXX_STANDARD 14)

set(COMMON_SOURCES
        src/impress.h
        src/impress/request.cpp src/impress/request.h
        src/impress/method.cpp src/impress/method.h
        src/impress/status.cpp src/impress/status.h)

add_library(impress_http STATIC ${COMMON_SOURCES})
target_include_directories(impress_http PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE impress_http)
