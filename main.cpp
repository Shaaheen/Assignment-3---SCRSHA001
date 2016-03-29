#include <iostream>
#include "HuffmanUtils.h"
#include "HuffmanTree.h"
using namespace std;

//int main(int argc,char* argv[]) {
//    //Check if right amount of arguments
//    if (argc !=3){
//        cout << "Incorrect arguments passed (Not enough or too little found) " <<endl;
//    }
//    else{
//        string inputFile = string(argv[1]);
//        string outputFile = string(argv[2]);
//        SCRSHA001::HuffmanUtils huffmanUtils = SCRSHA001::HuffmanUtils();
//        string wholeTextFromFile = huffmanUtils.readStringFromFile(inputFile);
//        SCRSHA001::HuffmanTree huffmanTree = SCRSHA001::HuffmanTree(wholeTextFromFile,outputFile);
//    }
//    return 0;
//}