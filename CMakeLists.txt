cmake_minimum_required(VERSION 3.18)
project(SemestralnaPracaUdSP C)

set(CMAKE_C_STANDARD 11)

# find libcurl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(SemestralnaPracaUdSP main.c
        sockets.c
        sockets.h
        huffman_structures/huffman_node.c
        huffman_structures/huffman_node.h
        huffman_structures/priority_queue.c
        huffman_structures/priority_queue.h
        huffman_structures/huffman_tree.c
        huffman_structures/huffman_tree.h
)

target_link_libraries(SemestralnaPracaUdSP ${CURL_LIBRARIES})
