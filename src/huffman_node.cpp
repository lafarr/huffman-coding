#include <array>
#include <string>
#include "../include/huffman_node.h"

Huffman_node::Huffman_node(std::string symbol, Node_type type) : m_symbol(symbol), m_weight(0.0), m_type(type)
{}

Huffman_node::Huffman_node(std::string symbol, double weight, Node_type type, std::array<std::shared_ptr<Huffman_node>, 2> children) 
    : m_symbol(symbol), m_weight(weight), m_type(type), m_children(children)
{}
