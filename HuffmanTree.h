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
            std::unordered_map<char,std::string> codeTable;

        public:
            HuffmanTree();
            HuffmanTree(std::string toEncode);
            ~HuffmanTree();
            std::unordered_map<char, int> createLetterFrequencyTable(const std::string &toEncode) const;

            std::shared_ptr<HuffmanNode> buildTree(
                std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, HuffmanComparator>& priorityQueue);

            void buildCodeTableFromTree(std::shared_ptr<HuffmanNode> rootNode,std::string bitString);

            std::string getCodeForLetter(char letter);

            std::string compressStringWithHuffman(std::string toEncode);

            void extractCompressedTextOut(const std::string &compressedString) const;

            void createCodeTableFile(std::unordered_map<char, int> &letterFrequencyTable, const std::string &codeTableName) const;
    };


}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
