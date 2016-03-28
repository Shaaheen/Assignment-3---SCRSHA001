//
// Created by Shaaheen on 3/27/2016.
//

#include <queue>
#include <fstream>
#include "HuffmanTree.h"
#include "catch.hpp"

using namespace std;

namespace SCRSHA001{

    HuffmanTree::HuffmanTree() { }

    HuffmanTree::~HuffmanTree() { }

    HuffmanTree::HuffmanTree(std::string toEncode) {

        unordered_map<char,int> letterFrequencyTable = createLetterFrequencyTable(toEncode); //Get frequency table

        //Priority queue prioritising the smallest frequency nodes first
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueOfNodes;

        //Add all letters with associated frequencies into priority queue in preparation to be attached to tree
        for (unordered_map<char, int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            priorityQueueOfNodes.push(shared_ptr<HuffmanNode>(new HuffmanNode(iterator->first,iterator->second)));
        }

        this->rootNode = buildTree(priorityQueueOfNodes); //Set root node to root of built Huffman Tree
        buildCodeTableFromTree(rootNode,""); //Sets the code table for tree

        string compressedString = compressStringWithHuffman(toEncode);

        extractCompressedTextOut(compressedString);
        string codeTableName = "CodeTable.txt";
        createCodeTableFile(letterFrequencyTable, codeTableName);


    }

    //Function to create a file with the code table informaion stored in it
    void HuffmanTree::createCodeTableFile(unordered_map<char, int> &letterFrequencyTable, const string &codeTableName) const {
        ofstream codeTableFile;
        codeTableFile.open(codeTableName);
        codeTableFile <<letterFrequencyTable.size() <<endl;
        //Loop through letters found and print the corresponding code table value
        for (unordered_map<char,int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            codeTableFile << iterator -> first << " " << codeTable.at(iterator->first) << endl;
        }
        codeTableFile.close();
    }

    //Function to write out the compressed string with associated code table values
    void HuffmanTree::extractCompressedTextOut(const string &compressedString) const {
        char * bytesFromCompressed = (char *) compressedString.c_str();
        ofstream file("outfile.bin", std::ios::binary);
        file.write(bytesFromCompressed,100);
        file.close();
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

        return lettersFound; //return the finished freq table
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