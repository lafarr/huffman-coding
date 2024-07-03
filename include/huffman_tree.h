#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <memory>
#include "huffman_node.h"

class Huffman_tree {
public:
    explicit Huffman_tree(const std::string &fname);

    std::unordered_map<char, long> encoding_mappings();
private:
    void build(); 

    std::string m_input_string;
    std::shared_ptr<Huffman_node> m_root;
    std::unordered_map<char, long> m_encoding_mappings;
};

#endif
