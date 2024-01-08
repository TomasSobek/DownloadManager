cmake_minimum_required(VERSION 3.18)
project(SemestralnaPracaUdSP C)

set(CMAKE_C_STANDARD 11)

# find libcurl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(SemestralnaPracaUdSP main.c
        sockets.c
        sockets.h
        file_transfer.c
        file_transfer.h
)

target_link_libraries(SemestralnaPracaUdSP ${CURL_LIBRARIES})
