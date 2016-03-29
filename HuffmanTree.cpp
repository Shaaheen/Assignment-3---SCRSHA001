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

    HuffmanTree::HuffmanTree(string toEncode,string outFileName) {
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

        huffmanUtils.extractCompressedTextOut(compressedString,outFileName);
        string codeTableName = "CodeTable.txt";
        huffmanUtils.createCodeTableFile(letterFrequencyTable, codeTableName,codeTable);


        extractUsingBitstream(compressedString);

    }

    /*
     * Function to take in a string representation of bits and join the bits together to a byte
     * Store those bytes in a buffer and then write buffer to binary outfile
    */
    void HuffmanTree::extractUsingBitstream(string &compressedString) const {
        ofstream stream("outfileFromBitstream.bin", ios_base::binary);
        cout<<compressedString.size()<<endl;
        cout<<(compressedString.size()/8) +1 <<endl;
        cout<<compressedString.substr(0,8)<<endl;
        char* buffer;
        int numberOfBits = compressedString.size();
        int numberOfBytesCreated = (numberOfBits/8) + (numberOfBits%8 ? 1:0); //Formula from assignment brief

        unsigned int getBitsFrom = 0;
        for (int i=0;  i < numberOfBytesCreated; ++i) {
            if ((getBitsFrom+8) >compressedString.size()){ //If last byte needs more bits from compressedString then fill with 0's
                int diff = (getBitsFrom+8) - compressedString.size();
                for (int j = 0; j < diff; ++j) {
                    compressedString = compressedString + "0"; //Add 0's that will be discarded just to make a whole byte now
                }
            }
            bitset<8> bitstream (compressedString.substr(getBitsFrom,getBitsFrom+8)); //Get bitstream from string representation
            uint8_t byte=0;
            for (size_t j=0; j<8; ++j){
                //byte = (byte << 1) | bitstream[i*8 + j];

//                if (bitstream[j] ==1){
//                    byte |= 1;
//                    //cout<<"vh "<<endl;
//                }
//                byte<<=1;

            }
            buffer[i] = (char) bitstream.to_ulong(); //Get char value(byte value) of bitstream to represent bits as a byte together
            //char byteA = (char) bitstream.to_ulong();

            getBitsFrom = getBitsFrom + 8;
        }

        stream.write((const char *) numberOfBits, sizeof(int)); //Prints number of bits in file in header
        stream.write((const char *) '\n',sizeof(int)); //New line
        stream.write(buffer, numberOfBytesCreated); //Print the stored bytes to the file
        stream.close();
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