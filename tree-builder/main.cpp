#include <fstream>
#include <iostream>

std::string getFileName(char* file) {
    size_t dot_pos = 0, file_len = strlen(file);
    for (size_t i = 0; i < file_len; ++i) {
        if (file[i] == '.') {
            dot_pos = i;
        }
    }
    std::string prefix(dot_pos, 0);

    for (size_t i = 0; i < dot_pos; ++i) {
        prefix[i] = file[i];
    }

    return prefix;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Required base file (only base file)";
        return 1;
    }

    auto file_name = getFileName(argv[1]);
    std::ifstream is(argv[1], std::ios::binary | std::ifstream::in);

    unsigned char cur_byte = 0;
    uint32_t byte_cnt[256];
    while (is >> cur_byte, !is.eof()) {
        byte_cnt[cur_byte]++;
    }

    std::ofstream os(file_name + ".tree", std::ofstream::binary);
    os.write((char*) &byte_cnt, 256);
    os.close();
}


// 00 00 03 12
// 12 30 00 00
