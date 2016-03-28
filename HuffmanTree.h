//
// Created by Shaaheen on 3/27/2016.
//

#ifndef ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
#define ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H


#include <memory>
#include <queue>
#include <unordered_map>
#include "HuffmanNode.h"

namespace SCRSHA001{
    //For the priority queue - Organising the smallest first
    struct HuffmanComparator
    {
        bool operator()(const std::shared_ptr<HuffmanNode> & a,const std::shared_ptr<HuffmanNode> & b) const
        {
            return !((*a) < (*b));
        }
    };

    class HuffmanTree {
        private:
            std::shared_ptr<HuffmanNode> rootNode;

        public:
            HuffmanTree();
            HuffmanTree(std::string toEncode);
            ~HuffmanTree();
            std::unordered_map<char, int> createLetterFrequencyTable(const std::string &toEncode) const;

            std::shared_ptr<HuffmanNode> buildTree(
                std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, HuffmanComparator>& priorityQueue);
    };


}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
