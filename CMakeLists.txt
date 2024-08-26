cmake_minimum_required(VERSION 3.20)
project(ImpressHttp)

set(CMAKE_CXX_STANDARD 14)

set(COMMON_SOURCES
        src/impress/impress.h
        src/impress/http/request.cpp src/impress/http/request.h
        src/impress/http/method.cpp src/impress/http/method.h
        src/impress/http/status.cpp src/impress/http/status.h
        src/impress/logging/logger.cpp
        src/impress/logging/logger.h
        src/impress/logging/stream_logger.cpp
        src/impress/logging/stream_logger.h)

add_library(impress_http STATIC ${COMMON_SOURCES})
target_include_directories(impress_http PUBLIC ${CMAKE_SOURCE_DIR}/src/impress)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE impress_http)
