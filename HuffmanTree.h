//
// Created by Shaaheen on 3/27/2016.
//

#ifndef ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
#define ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H


#include <bits/shared_ptr.h>
#include "HuffmanNode.h"

namespace SCRSHA001{
    class HuffmanTree {
        private:
            std::shared_ptr<HuffmanNode> rootNode;

        public:
            HuffmanTree();
            ~HuffmanTree();
    };
}



#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANTREE_H
