//
// Created by Shaaheen on 3/27/2016.
//

#include <queue>
#include "HuffmanTree.h"
#include "catch.hpp"

using namespace std;

namespace SCRSHA001{

    HuffmanTree::HuffmanTree() {

    }

    HuffmanTree::~HuffmanTree() {

    }

    HuffmanTree::HuffmanTree(std::string toEncode) {

        unordered_map<char,int> letterFrequencyTable = createLetterFrequencyTable(toEncode); //Get frequency table

        //Priority prioritising the smallest frequency nodes first
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueOfNodes;

        //Add all letters with associated frequencies into priority queue in preparation to be attached to tree
        for (unordered_map<char, int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            priorityQueueOfNodes.push(shared_ptr<HuffmanNode>(new HuffmanNode(iterator->first,iterator->second)));
        }

        buildTree(priorityQueueOfNodes);

    }
    std::shared_ptr<SCRSHA001::HuffmanNode> HuffmanTree::buildTree(priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> &priorityQueue)
    {
        shared_ptr<HuffmanNode> leftOfNewParent = priorityQueue.top();
        cout<<"Left Node: "<<leftOfNewParent.use_count()<<endl;
        priorityQueue.pop();
        cout<<"Left Node: "<<leftOfNewParent.use_count()<<endl;
        shared_ptr<HuffmanNode> rightOfNewParent = priorityQueue.top();
        priorityQueue.pop();
        int parentFrequency = (*leftOfNewParent).getFrequency() + (*rightOfNewParent).getFrequency();

        shared_ptr<HuffmanNode> newParentNode(new HuffmanNode('_',parentFrequency));
        newParentNode->left = leftOfNewParent;
        newParentNode->right = rightOfNewParent;
        cout<<"Left Node last: "<<leftOfNewParent.use_count()<<endl;
        priorityQueue.push(newParentNode);
        cout<<"Left Node after push: "<<leftOfNewParent.use_count()<<endl;
        return newParentNode;
    }

    unordered_map<char, int> HuffmanTree::createLetterFrequencyTable(const string &toEncode) const {

        char * lettersInTextFile = (char *) toEncode.c_str(); //Separate string into char array
        unordered_map<char,int> lettersFound;// = unordered_map<char,int>();

        //Iterate through letters in file
        for (int i = 0; i < toEncode.length(); ++i) {
            //const _Hashtable<char,int>::key_type currentLetter = lettersInTextFile[i]; //Get the ith letter
            const unordered_map<char,int>::iterator got = lettersFound.find(lettersInTextFile[i]); //Check if already in map
            if (got  != lettersFound.end()){ //Found Letter
                got->second = got->second + 1; //add one to frequency since another occurence found
            }
            else{
                lettersFound.insert({lettersInTextFile[i],1}); //insert into table the new letter
            }
        }

        return lettersFound;
    }



}