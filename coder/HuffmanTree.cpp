//
// Created by Тимур Ахметзянов on 26.02.2025.
//

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(const char *tree_file) {
    uint32_t byte_cnt[256];
    for (unsigned int & i : byte_cnt) {
        i = 0;
    }
    std::ifstream readBuffer(tree_file, std::ifstream::binary);
    readBuffer.read((char*)&byte_cnt, 1024);

    std::cout << 0;
}
