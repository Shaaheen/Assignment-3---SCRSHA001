//
// Created by Shaaheen on 3/27/2016.
//

#include "HuffmanNode.h"

namespace SCRSHA001{
    //Default constructor
    HuffmanNode::HuffmanNode() { }

    //Destructor constructor
    HuffmanNode::~HuffmanNode() { }

    //Copy constructor
    HuffmanNode::HuffmanNode(const HuffmanNode &rhs) : left(new HuffmanNode(*rhs.left)), right(new HuffmanNode(*rhs.right)){
        this->frequency = rhs.frequency;
        this->letter = rhs.letter;
    }

    //Move constructor
    HuffmanNode::HuffmanNode(HuffmanNode &&rhs) {
        left = std::move(rhs.left);
        right = std::move(rhs.right);
        this->letter = std::move(rhs.letter);
        this->frequency = std::move(rhs.frequency);
    }

    //Copy assignment operator
    HuffmanNode &HuffmanNode::operator=(const HuffmanNode &rhs) {
        this->letter = rhs.letter;
        this->frequency = rhs.frequency;
        this->left.operator=(rhs.left);
        this->right.operator=(rhs.right);
        return *this;
    }

    //Move assignment operator
    HuffmanNode &HuffmanNode::operator=(const HuffmanNode &&rhs) {
        this->left = std::move(rhs.left);
        this->right = std::move(rhs.right);
        this->letter = std::move(rhs.letter);
        this->frequency = std::move(rhs.frequency);
        return *this;
    }

    //constructor to build a node
    HuffmanNode::HuffmanNode(char lett, int freq) {
        this->letter = lett;
        this->frequency = freq;
    }

    //Function to hancle to "<" operation
    bool HuffmanNode::operator<(const HuffmanNode &rhs)const {
        return (this->frequency < rhs.getFrequency());
    }
    
    int HuffmanNode::getFrequency() const{
        return frequency;
    }

    char HuffmanNode::getLetter() const {
        return letter;
    }

}
