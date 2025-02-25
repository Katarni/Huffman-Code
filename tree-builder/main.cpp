#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Required base file (only base file)";
        return -1;
    }

    std::ifstream is(argv[1]);
    unsigned char cur_byte = 0;
    int byte_cnt[256];
    while (!is.eof()) {
        is >> cur_byte;
        byte_cnt[cur_byte]++;
    }
}
