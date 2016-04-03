#include <iostream>
#include "HuffmanUtils.h"
#include "HuffmanTree.h"
using namespace std;

int main(int argc,char* argv[]) {
    //Check if right amount of arguments
    if (argc !=3){
        cout << "Incorrect arguments passed (Not enough or too little found) " <<endl;
    }
    else{
        //Get file names
        string inputFile = string(argv[1]);
        string outputFile = string(argv[2]);
        SCRSHA001::HuffmanUtils huffmanUtils = SCRSHA001::HuffmanUtils(); //get utility class
        string wholeTextFromFile = huffmanUtils.readStringFromFile(inputFile); //Get the text from a file
        SCRSHA001::HuffmanTree huffmanTree = SCRSHA001::HuffmanTree(wholeTextFromFile,outputFile); //Create huffman tree
        string answer;
        cout<<"Would you like to read in stream from bit packed huffman encode file (y or n)"<<endl;
        cin>>answer;
        if (answer =="y" || answer == "Y"){
            cout<<huffmanTree.readInUsingBitstream(outputFile)<<endl;
        }
    }
    return 0;
}