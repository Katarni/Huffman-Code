#include "HuffmanTree.h"

int main(int argc, char** argv) {
    if (argc < 3 || 4 < argc) {
        std::cerr << "Incorrect args count";
        return 1;
    }

    auto tree = HuffmanTree(argv[0]);
}