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

    bool compare(HuffmanNode a,HuffmanNode b){
        return (a < b) ;
    }
//    bool HuffmanTree::compare(const HuffmanNode &a, const HuffmanNode &b) {
//        return (a < b) ;
//    }

    HuffmanTree::HuffmanTree(std::string toEncode) {

        unordered_map<char,int> letterFrequencyTable = createLetterFrequencyTable(toEncode); //Get frequency table

        //Priority prioritising the smallest frequency nodes first
        priority_queue<HuffmanNode,vector<HuffmanNode>,HuffmanComparator> priorityQueueOfNodes;





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