//
// Created by Тимур Ахметзянов on 26.02.2025.
//

#pragma once

#include <iostream>
#include <fstream>
#include <set>


class HuffmanTree {
 public:
    explicit
    HuffmanTree(const char* tree_file);

    std::string encode(const char* file);

 private:
    struct Node {
        size_t weight;
        char byte;
        Node *left, *right;

        explicit
        Node(size_t _weight) : byte(0), weight(_weight),
                                left(nullptr), right(nullptr) {}

        explicit
        Node(char _byte, size_t _weight) : byte(_byte), weight(_weight),
                                            left(nullptr), right(nullptr) {}
    };

    Node* root;
    std::string* codes;

    void fillCodes(Node* t, std::string code = "");
    std::string getFileName(const char* file);
};
