//
// Created by Shaaheen on 3/27/2016.
//

#ifndef ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H
#define ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H


#include <string>
#include <memory>

namespace SCRSHA001{
    class HuffmanNode {
    private:
        char letter;
        int frequency;
    public:
        std::shared_ptr<HuffmanNode> left = nullptr;
        std::shared_ptr<HuffmanNode> right = nullptr;

        HuffmanNode(char lett,int freq);

        bool operator<(const HuffmanNode &rhs)const;
        int getFrequency() const;
        char getLetter() const;
    };
}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H
