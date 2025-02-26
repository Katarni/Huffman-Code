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
    std::ifstream readBuffer(argv[1], std::ios::binary | std::ifstream::in);

    uint32_t byte_cnt[256];
    for (int i = 0; i < 256; ++i) {
        byte_cnt[i] = 0;
    }
    std::string line;
    while (getline(readBuffer, line)) {
        for (unsigned char cur_byte : line) {
            byte_cnt[cur_byte]++;
        }
        byte_cnt['\n']++;
    }

    std::ofstream writeBuffer(file_name + ".tree", std::ofstream::binary);

    writeBuffer.write((char*) &byte_cnt, 4*256);
    writeBuffer.close();
    readBuffer.close();
}


// 00 00 03 12
// 12 30 00 00
