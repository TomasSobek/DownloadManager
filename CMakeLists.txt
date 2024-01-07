cmake_minimum_required(VERSION 3.18)
project(SemestralnaPracaUdSP C)

set(CMAKE_C_STANDARD 11)

add_executable(SemestralnaPracaUdSP main.c
        tcp_client.c
        tcp_server.c
)
