//
// Created by Shaaheen on 3/27/2016.
//

#include <queue>
#include <fstream>
#include <bitset>
#include "HuffmanTree.h"
#include "catch.hpp"
#include "HuffmanUtils.h"

using namespace std;

namespace SCRSHA001{

    HuffmanTree::HuffmanTree() { }

    HuffmanTree::~HuffmanTree() { }

    HuffmanTree::HuffmanTree(std::string toEncode) {
        HuffmanUtils huffmanUtils = HuffmanUtils();
        unordered_map<char,int> letterFrequencyTable = huffmanUtils.createLetterFrequencyTable(toEncode); //Get frequency table

        //Priority queue prioritising the smallest frequency nodes first
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueOfNodes;

        //Add all letters with associated frequencies into priority queue in preparation to be attached to tree
        for (unordered_map<char, int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            priorityQueueOfNodes.push(shared_ptr<HuffmanNode>(new HuffmanNode(iterator->first,iterator->second)));
        }

        this->rootNode = buildTree(priorityQueueOfNodes); //Set root node to root of built Huffman Tree
        buildCodeTableFromTree(rootNode,""); //Sets the code table for tree

        string compressedString = compressStringWithHuffman(toEncode);

        huffmanUtils.extractCompressedTextOut(compressedString);
        string codeTableName = "CodeTable.txt";
        huffmanUtils.createCodeTableFile(letterFrequencyTable, codeTableName,codeTable);

        ofstream stream("outfileForBitstream.bin", std::ios::binary);
        //bitset<8> bitstream (compressedString);
        //cout<<bitstream<<endl;
        cout<<compressedString.size()<<endl;
        cout<<(compressedString.size()/8) +1 <<endl;
        int getBitsFrom = 0;
        for (size_t i=0, n=(compressedString.size()/8)+1; i<n; ++i) {
            bitset<8> bitstream (compressedString.substr(getBitsFrom,getBitsFrom+8));
            //cout<<"loopty loop"<<endl;
            uint8_t byte=0;
            for (size_t j=0; j<8; ++j){
                byte = (byte << 1) | bitstream[i*8 + j];
//                if (bitstream[j] ==1){
//                    byte |= 1;
//                }
//                byte<<=1;
            }
                //byte = (byte << 1) | bitstream[i*8 + j];
            //cout<<byte<<endl;
            stream.write((const char *) &byte, sizeof(byte));
            getBitsFrom = getBitsFrom + 8;
        }
        stream.close();

        ifstream f("outfileForBitstream.bin", ios::binary | ios::in);
        char c;
        while (f.get(c))
        {
            for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
                cout << ((c >> i) & 1);
        }


    }

    //Traverses tree and adds appropriate bitstring character
    void HuffmanTree::buildCodeTableFromTree(std::shared_ptr<HuffmanNode> rootNode,string bitString) {
        if (rootNode->left != nullptr){
            buildCodeTableFromTree(rootNode->left,bitString + "0"); //If traverse left - add 0 to bitstring
        }
        this->codeTable.insert({(*rootNode).getLetter(),bitString}); //Set the code table with bitstring and associated letter
        if (rootNode->right != nullptr){
            buildCodeTableFromTree(rootNode->right,bitString + "1"); //If traverse right - add 1 to bitstring
        }
    }


    shared_ptr<HuffmanNode> HuffmanTree::buildTree(priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> &priorityQueue)
    {
        shared_ptr<HuffmanNode> newParentNode = nullptr;
        //Loops until all nodes linked together and all thats left is the root node
        while (priorityQueue.size() > 1){

            //Get the smallest frequency letter as a Huffman Node - this will be the left node of the new parent
            shared_ptr<HuffmanNode> leftOfNewParent = priorityQueue.top();
            priorityQueue.pop();
            //Get the second smallest frequency letter - right side of parent
            shared_ptr<HuffmanNode> rightOfNewParent = priorityQueue.top();
            priorityQueue.pop();
            //Frequency of parent is the summation of the frequency of its children
            int parentFrequency = (*leftOfNewParent).getFrequency() + (*rightOfNewParent).getFrequency();

            newParentNode.reset(new HuffmanNode('_',parentFrequency)); //Empty char and summed frequency
            newParentNode->left = leftOfNewParent; //Set pointers from parent to the children nodes so they don't get lost(out of scope)
            newParentNode->right = rightOfNewParent;
            priorityQueue.push(newParentNode); //Push new parent node onto priority queue to be possibly merged again
        }

        return newParentNode; //return the last edited node - root node
    }

    //Function to return the bitstring code for a specified letter
    std::string HuffmanTree::getCodeForLetter(char letter) {
        return codeTable.at(letter);
    }

    //Function to use the code table to match up the letters in a string and change them to the code table equivalent
    std::string HuffmanTree::compressStringWithHuffman(std::string toEncode) {
        char * lettersInTextFile = (char *) toEncode.c_str(); //Split into letter array
        string compressedString = "";
        for (int i = 0; i < toEncode.length(); ++i) {
            compressedString = compressedString + codeTable.at(lettersInTextFile[i]); //Add code value of that letter
        }
        return compressedString; //return full coded string
    }
}