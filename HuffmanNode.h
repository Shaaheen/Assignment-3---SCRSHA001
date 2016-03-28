//
// Created by Shaaheen on 3/27/2016.
//

#ifndef ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H
#define ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H


#include <string>

namespace SCRSHA001{
    class HuffmanNode {
    private:
        char letter;
        int frequency;
    public:
        HuffmanNode(char lett,int freq);
        bool operator<(const HuffmanNode &rhs)const;
        int getFrequencey();
    };
}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANNODE_H
