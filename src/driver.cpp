#include "../include/driver.h"
#include "../include/huffman_tree.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <bit>

void compress_file(const std::string &fname) {
    // get last occurrence of '.' and replace after that with .compressed
    std::vector<typename std::string::size_type> idxs;
    
    std::string::size_type idx;
    int start_idx{ 0 };
    while ((idx = fname.find(".", start_idx)) != std::string::npos) {
        idxs.push_back(idx);
        start_idx = idx + 1;
    }

    std::string new_fname{};
    if (idxs.size()) {
        new_fname = fname.substr(0, idxs.at(idxs.size() - 1) + 1) + "huf";
    } else {
        new_fname = fname + ".huf";
    }

    std::cout << "before" << '\n';
    Huffman_tree tree{ fname };
    std::cout << "after" << '\n';
    std::unordered_map<char, long> mappings = Huffman_tree{ fname }.encoding_mappings();
    std::cout << "{ ";
    std::cout << " }";
    std::ofstream ofstream{ new_fname, std::ios::binary };
    std::ifstream ifstream{ fname };
    std::string line;
    while (std::getline(ifstream, line)) {
        for (char ch : line) {
            // TODO: Make it so we write 1 byte at a time, and make sure sizeof(file) = 8 * k
            ofstream.write(std::bit_cast<char*>(&mappings.at(ch)), sizeof(long));
        }
    }
}
