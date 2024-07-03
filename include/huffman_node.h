#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <memory>
#include <array>
#include <unordered_map>
#include <string>

enum Node_type { internal, leaf };

class Huffman_node {
public:
    Huffman_node(std::string symbol, Node_type type);

    Huffman_node(std::string symbol, double weight, Node_type type, std::array<std::shared_ptr<Huffman_node>, 2> children); 

    double weight() {
        return m_weight;
    }

    std::string symbol() {
        return m_symbol;
    }

    void set_parent(std::shared_ptr<Huffman_node> parent) {
        m_parent = parent;
    }

    Node_type type() {
        return m_type;
    }

    std::array<std::shared_ptr<Huffman_node>, 2> children() {
        return m_children;
    }

private:
    std::string m_symbol;
    std::shared_ptr<Huffman_node> m_parent;
    double m_weight;
    std::array<std::shared_ptr<Huffman_node>, 2> m_children;
    Node_type m_type;
};

#endif
