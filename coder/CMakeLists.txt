cmake_minimum_required(VERSION 3.28.1)
project(huffman-coder)

set(CMAKE_CXX_STANDARD 23)

add_executable(huffman-coder
        HuffmanTree.cpp
        HuffmanTree.h
        coder.cpp
)
