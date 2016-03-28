//
// Created by Shaaheen on 3/27/2016.
//

#ifndef ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
#define ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H


#include <memory>
#include <unordered_map>
#include "HuffmanNode.h"

namespace SCRSHA001{
    class HuffmanTree {
        private:
            std::shared_ptr<HuffmanNode> rootNode;

        public:
            HuffmanTree();
            HuffmanTree(std::string toEncode);
            ~HuffmanTree();
            std::unordered_map<char, int> createLetterFrequencyTable(const std::string &toEncode) const;
            bool compare(const HuffmanNode& a,const HuffmanNode& b);

    };
}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
