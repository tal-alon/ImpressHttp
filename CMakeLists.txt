cmake_minimum_required(VERSION 3.20)
project(ImpressHttp)

set(CMAKE_CXX_STANDARD 14)

set(COMMON_SOURCES
        src/impress/impress.h
        src/impress/http/request.cpp src/impress/http/request.h
        src/impress/http/method.h
        src/impress/http/status.cpp src/impress/http/status.h
        src/impress/http/path.cpp src/impress/http/path.h

        src/impress/logging/logger.cpp src/impress/logging/logger.h
        src/impress/logging/stream_logger.cpp src/impress/logging/stream_logger.h

        src/impress/server/server.cpp src/impress/server/server.h
        src/impress/server/connection.cpp src/impress/server/connection.h
        src/impress/server/router.cpp src/impress/server/router.h
        src/impress/http/response.cpp src/impress/http/response.h
        src/impress/http/headers.cpp src/impress/http/headers.h

        src/impress/socket/wsa_initializer.cpp
        src/impress/socket/wsa_initializer.h
        src/impress/socket/socket.cpp
        src/impress/socket/socket.h
        src/impress/socket/socket_error.cpp
        src/impress/socket/socket_error.h
)

add_library(impress_http STATIC ${COMMON_SOURCES})
target_include_directories(impress_http PUBLIC ${CMAKE_SOURCE_DIR}/src/impress)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE impress_http)
