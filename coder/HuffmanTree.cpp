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
    readBuffer.close();

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

    codes.resize(256);
    for (int i = 0; i < 256; ++i) {
        codes[i] = "";
    }

    fillCodes(root);
}

void HuffmanTree::fillCodes(HuffmanTree::Node *t, std::string code) {
    if (t->left == nullptr && t->right == nullptr) {
        codes[t->byte] = code;
        return;
    }

    code.push_back(0);
    fillCodes(t->left, code);
    code.back() = 1;
    fillCodes(t->right, code);
}

std::string HuffmanTree::encode(const char *file) {
    std::ifstream readFile(file, std::ios::binary | std::ifstream::in);
    readFile.seekg(0, std::ios::end);
    size_t file_size = readFile.tellg();
    readFile.seekg(0, std::ios::beg);

    char* data = new char[file_size];
    readFile.read(data, (int)file_size);

    uint64_t output_size = 0;
    std::string output_data;
    for (int i = 0; i < file_size; ++i) {
        output_size += codes[(unsigned char)data[i]].size();
        output_data += codes[(unsigned char)data[i]];
    }

    std::string out_file = getFileName(file) + "-encode.packed";

    std::ofstream os(out_file, std::ios::binary);
    os.write((char*)&output_size, 8);
    char cur_byte = 0;
    int cnt = 0;
    for (int i = 0; i < output_size; ++i, cnt = (cnt + 1) % 8) {
        if (i != 0 && cnt == 0) {
            os.write(&cur_byte, 1);
            cur_byte = 0;
            cnt = 0;
        }
        if (output_data[i] == 1) {
            cur_byte |= 1 << (7 - i % 8);
        }
    }
    os.write(&cur_byte, 1);

    os.close();
    return out_file;
}

std::string HuffmanTree::getFileName(const char *file) {
    int dot_pos = 0;
    for (int i = 0; i < strlen(file); ++i) {
        if (file[i] == '.') {
            dot_pos = i;
        }
    }

    return {file, file + dot_pos};
}

std::string HuffmanTree::decode(const char *file) {
    std::ifstream readEncode(file, std::ios::binary | std::ifstream::in);

    readEncode.seekg(0, std::ios::end);
    int byte_file_size = (int)readEncode.tellg();
    readEncode.seekg(0, std::ios::beg);

    char *data = new char[byte_file_size];
    readEncode.read(data, byte_file_size);

    uint64_t data_file_size = 0;
    for (int i = 0; i < 8; ++i) {
        data_file_size |= (int64_t)data[i] << (8 * (8 - i));
    }

    Node* cur = root;

    std::ofstream outFile(getFileName(file) + "-decoded.txt", std::ios::binary);
    int j = 0;
    for (int byte = 8; byte < byte_file_size; ++byte) {
        for (int i = 7; i >= 0 && j < data_file_size; --i, ++j) {
            if (data[byte]&(1 << i)) {
                cur = cur->right;
            } else {
                cur = cur->left;
            }

            if (cur->is_term) {
                outFile.write(&cur->byte, 1);
                cur = root;
            }
        }
    }
    outFile.close();
    return getFileName(file) + "-decoded.txt";
}
