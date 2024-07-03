#include <fstream>
#include <unordered_map>
#include <iostream>
#include "../include/huffman_tree.h"

Huffman_tree::Huffman_tree(const std::string &fname) : m_input_string("") {
    std::ifstream istream{ fname };
    std::ofstream ostream{ "tmp.compressed" };
    std::string line;
    while (std::getline(istream, line)) {
        for (char ch : line) {
            m_input_string += ch;
        }
    }
    build();
}

std::unordered_map<char, long> Huffman_tree::encoding_mappings() {
    return m_encoding_mappings;
}

void Huffman_tree::build() {
    std::unordered_map<char, double> counts;
    // get probabilities
    for (char ch : m_input_string) {
        double curr_count = counts[ch];
        if (curr_count == 0.0) {
            counts[ch] = 1.0;
        } else {
            counts[ch] = curr_count + 1.0;
        }
    } 
    double word_count = 0.0;
    for (auto [key, value] : counts) {
        word_count += value;
    }
    for (auto &[key, value] : counts) {
        value = value / word_count;
        std::cout << "value: " << value << '\n';
    }

    // insert all nodes into priority queue
    auto cmp = [](std::shared_ptr<Huffman_node> first, std::shared_ptr<Huffman_node> second){ return first->weight() > second->weight(); };
    std::priority_queue<std::shared_ptr<Huffman_node>, std::vector<std::shared_ptr<Huffman_node>>, decltype(cmp)> pq(cmp);
    for (auto &[key, value] : counts) {
        pq.push(std::make_shared<Huffman_node>(Huffman_node{ std::string{ 1, key }, value, leaf, {} }));
    }

    // take 2 nodes with lowest probs, make new internal node with those two as children and the sum of their weights as its weight
    while (pq.size() > 1) {
        std::shared_ptr<Huffman_node> first = pq.top();
        pq.pop();
        std::shared_ptr<Huffman_node> second = pq.top();
        pq.pop();
        std::string combined_symbol = first->symbol() + second->symbol();
        double combined_weight = first->weight() + second->weight(); 
        std::cout << "combined: " << std::to_string(combined_weight) << '\n';
        std::array<std::shared_ptr<Huffman_node>, 2> children{ first, second };
        std::shared_ptr<Huffman_node> internal_node = std::make_shared<Huffman_node>(Huffman_node{ combined_symbol, combined_weight, internal, children });
        first->set_parent(internal_node);
        second->set_parent(internal_node);
        pq.push(internal_node);
    }

    // Generate mapping from character to encoding
    for (auto [ch, prob] : counts) {
        // find ch in tree, and keep track of encoding along the way
        std::shared_ptr<Huffman_node> curr_node = pq.top();
        int levels_deep = 0;
        std::string current_encoding = "";
        while (curr_node->type() == internal) {
            std::shared_ptr<Huffman_node> left_child = curr_node->children()[0];
            std::shared_ptr<Huffman_node> right_child = curr_node->children()[1];
            if (left_child->symbol().find(ch) != std::string::npos) {
                current_encoding.append("0");
                curr_node = left_child;
            } else {
                current_encoding.append("1") ;
                curr_node = right_child;
            }
        }
        std::cout << std::string(1, ch) << " " << current_encoding << '\n';
        long bit_encoding = 0;
        for (int i = 0; i < current_encoding.size(); ++i) {
            bit_encoding |= (current_encoding.at(i) - '0') << (current_encoding.size() - 1 - i);
        }
        m_encoding_mappings[ch] = bit_encoding;
    }
    std::cout << "Here we go..." << std::endl;
    std::cout << "{ " << '\n';
    for (auto &[key, value] : m_encoding_mappings) {
        std::cout << key << ":" << value << " & ";
    }
    std::cout << " }" << '\n';
}
