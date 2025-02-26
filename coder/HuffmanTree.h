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
    std::string decode(const char* file);

 private:
    struct Node {
        size_t weight;
        char byte;
        Node *left, *right;
        bool is_term;

        explicit
        Node(size_t _weight) : byte(0), weight(_weight),
                                left(nullptr), right(nullptr),
                                is_term(false) {}

        explicit
        Node(char _byte, size_t _weight) : byte(_byte), weight(_weight),
                                            left(nullptr), right(nullptr),
                                            is_term(true) {}
    };

    Node* root;
    std::vector<std::string> codes;

    void fillCodes(Node* t, std::string code = "");
    static std::string getFileName(const char* file);
};
