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

    std::set<Node*, decltype(
    [](const Node *a, const Node *b) {
        if (a->weight == b->weight) {
            return a->byte <= b->byte;
        }
        return a->weight < b->weight;
    }
    )> node_builder;

    for (int i = 0; i < 256; ++i) {
        if (byte_cnt[i] == 0) continue;
        node_builder.insert(new Node(static_cast<char>(i), byte_cnt[i]));
    }

    while (node_builder.size() > 1) {
        auto left = *node_builder.begin();
        node_builder.erase(node_builder.begin());
        auto right = *node_builder.begin();
        node_builder.erase(node_builder.begin());

        auto center = new Node(left->weight + right->weight);
        center->left = left;
        center->right = right;

        node_builder.insert(center);
    }

    root = *node_builder.begin();
}
