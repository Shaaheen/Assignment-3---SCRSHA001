//
// Created by Shaaheen on 3/27/2016.
//

#include <queue>
#include <fstream>
#include <bitset>
#include <unordered_map>
#include "HuffmanTree.h"
#include "catch.hpp"
#include "HuffmanUtils.h"

using namespace std;

namespace SCRSHA001{

    HuffmanTree::HuffmanTree() { }

    HuffmanTree::~HuffmanTree() { }

    //Copy constructor
    HuffmanTree::HuffmanTree(const HuffmanTree & rhs) : rootNode(new HuffmanNode(*rhs.rootNode)) {
        this->letterFrequencyTable = rhs.letterFrequencyTable;
        this->charToCodeTable = rhs.charToCodeTable;
    }

    //Copy assignment operator
    HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhs) {
        this->letterFrequencyTable = rhs.letterFrequencyTable;
        this->charToCodeTable = rhs.charToCodeTable;
        rootNode.operator=(rhs.rootNode);
        return *this;
    }

    //Move constructor
    HuffmanTree::HuffmanTree(HuffmanTree &&rhs): rootNode(new HuffmanNode(*rhs.rootNode)) {
        this->letterFrequencyTable = move(rhs.letterFrequencyTable);
        this->charToCodeTable = move(rhs.charToCodeTable);
        delete rhs.rootNode;
        rhs.charToCodeTable.clear();
        rhs.letterFrequencyTable.clear();
    }

    //Move assignment operator
    HuffmanTree & operator=(HuffmanTree && rhs) {
        this->rootNode = move(rhs.rootNode);
        this->letterFrequencyTable = move(rhs.letterFrequencyTable);
        this->charToCodeTable = move(rhs.charToCodeTable);
        return *this;
    }



    HuffmanTree::HuffmanTree(string toEncode,string outFileName) {
        HuffmanUtils huffmanUtils = HuffmanUtils();
        this->letterFrequencyTable = huffmanUtils.createLetterFrequencyTable(toEncode); //Get frequency table

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
        string codeTableName = outFileName + "CodeTable.txt";
        huffmanUtils.createCodeTableFile(letterFrequencyTable, codeTableName,charToCodeTable);


        int sizeOfEncodedFile = huffmanUtils.extractUsingBitstream(compressedString,outFileName);
        int sizeOfOriginal = toEncode.length() * sizeof(char);
        double percentageReduction = ((sizeOfOriginal+0.0-sizeOfEncodedFile+0.0)/sizeOfOriginal+0.0)*100.0;
        cout<<"File size of huffman encoded file Bitstream"<<outFileName<<" in bytes: "<<sizeOfEncodedFile<<endl;
        cout<<"File size of original file in bytes: "<<sizeOfOriginal<<endl;
        cout<<"File reduced in size by "<<percentageReduction<<"%"<<endl;
        cout<<endl;

        //readInUsingBitstream(outFileName,letterFrequencyTable,charToCodeTable);
    }

    string HuffmanTree::readInUsingBitstream(const string &fileNameOfBitStream){

        HuffmanUtils huffmanUtils = HuffmanUtils();
        unordered_map<string,char> codeToCharTable = huffmanUtils.createCodeToCharTable(letterFrequencyTable,charToCodeTable);

        //string representation the huffman tree created before
        ifstream f("Bitstream" + fileNameOfBitStream, ios::binary | ios::in);
        int numOfBitsInFile = 0;
        char newline;
        f.read((char*)&numOfBitsInFile, sizeof(numOfBitsInFile));
        f.read((char*)&newline, sizeof(newline)); //Extracts new line character
        char c;
        int bitsRetrieved = 0; //Counts all the bits retrieved so to know when to stop reading
        string concat = ""; //Will keep adding bits until found a match in the code table
        string outputResult = "";  //Full result of added up chars

        while (f.get(c) )
        {
            for (int i = 7; i >= 0; i--){
                int bit = ((c >> i) & 1);
                if (bitsRetrieved < numOfBitsInFile){ //Stop reading if reached bits received
                    concat = concat + to_string(bit); //Add bits to going string
                    bitsRetrieved++;
                }
                //Tries to find char value for current bitstream
                unordered_map<std::string,char>::iterator got = codeToCharTable.find (concat);
                if (got != codeToCharTable.end()){ //if found
                    outputResult = outputResult + got->second; //Add char to result
                    concat=""; //reset bit string
                }
            }

        }
        f.close();
        return outputResult;
    }

    //Traverses tree and adds appropriate bitstring character
    void HuffmanTree::buildCodeTableFromTree(std::shared_ptr<HuffmanNode> rootNode,string bitString) {
        if (rootNode->left != nullptr){
            buildCodeTableFromTree(rootNode->left,bitString + "0"); //If traverse left - add 0 to bitstring
        }
        this->charToCodeTable.insert({(*rootNode).getLetter(),bitString}); //Set the code table with bitstring and associated letter
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

            newParentNode.reset(new HuffmanNode('\0',parentFrequency)); //Empty char and summed frequency
            newParentNode->left = leftOfNewParent; //Set pointers from parent to the children nodes so they don't get lost(out of scope)
            newParentNode->right = rightOfNewParent;
            priorityQueue.push(newParentNode); //Push new parent node onto priority queue to be possibly merged again
        }

        return newParentNode; //return the last edited node - root node
    }

    //Function to return the bitstring code for a specified letter
    std::string HuffmanTree::getCodeForLetter(char letter) {
        return charToCodeTable.at(letter);
    }

    //Function to use the code table to match up the letters in a string and change them to the code table equivalent
    std::string HuffmanTree::compressStringWithHuffman(std::string toEncode) {
        char * lettersInTextFile = (char *) toEncode.c_str(); //Split into letter array
        string compressedString = "";
        for (int i = 0; i < toEncode.length(); ++i) {
            compressedString = compressedString + charToCodeTable.at(lettersInTextFile[i]); //Add code value of that letter
        }
        return compressedString; //return full coded string
    }



}