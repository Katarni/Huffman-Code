#include "HuffmanTree.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Incorrect args count";
        return 1;
    }

    auto tree = HuffmanTree(argv[2]);

    if (strcmp(argv[1], "-e") == 0) {
        std::cout << "Encoded file: " + tree.encode(argv[3]) << std::endl;
    } else {

    }
}