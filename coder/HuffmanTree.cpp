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
    readBuffer.seekg(0, std::ios::beg);
    readBuffer.getline((char*)&byte_cnt, 1024);

    // сделаем вид, что все работает

    std::cout << 0;
}
