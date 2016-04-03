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
        //Points to children nodes
        std::shared_ptr<HuffmanNode> left = nullptr;
        std::shared_ptr<HuffmanNode> right = nullptr;

        //Constructor
        HuffmanNode();
        HuffmanNode(char lett,int freq);
        ~HuffmanNode();
        HuffmanNode(const HuffmanNode & rhs);
        HuffmanNode(HuffmanNode && rhs);

        //For equals operator constructor
        HuffmanNode & operator=(const HuffmanNode & rhs);
        //For equals operator constructor
        HuffmanNode & operator=(const HuffmanNode && rhs);

        bool operator<(const HuffmanNode &rhs)const;
        int getFrequency() const;
        char getLetter() const;
    };
}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H
