//
// Created by Shaaheen on 3/27/2016.
//

#include "HuffmanNode.h"

namespace SCRSHA001{
    HuffmanNode::HuffmanNode(char lett, int freq) {
        this->letter = lett;
        this->frequency = freq;
    }

//    bool operator<(HuffmanNode &rhs){
//        return (this->frequency < rhs.frequency);
//    }
    bool HuffmanNode::operator<(const HuffmanNode &rhs)const {
        return (this->frequency < rhs.frequency);
    }

    int HuffmanNode::getFrequencey() {
        return frequency;
    }
}
