//
// Created by Shaaheen on 3/28/2016.
//
#define CATCH_CONFIG_MAIN
//#include "../catch.hpp"

#include "HuffmanUnitTests.h"
#include "../HuffmanTree.h"
#include "../HuffmanNode.h"
#include "../HuffmanUtils.h"
#include <unordered_map>
#include <queue>
#include <memory>

using namespace std;
using namespace SCRSHA001;

//TEST_CASE("Huffman tree building and destroying","[HuffmanTree]"){
//
//    HuffmanTree huffmanTree = HuffmanTree();
//    HuffmanUtils huffmanUtils = HuffmanUtils();
//
//    SECTION("Testing letter frequency table"){
//        string textFileTestCase = "Hello Worldzies hit the hammer heavy xxxxxxx";
//        unordered_map<char,int> letterFrequencyMap = huffmanUtils.createLetterFrequencyTable(textFileTestCase);
//
//        REQUIRE( int(letterFrequencyMap.at('H')) == 1);
//        REQUIRE( int(letterFrequencyMap.at('h')) == 4);
//        REQUIRE( int(letterFrequencyMap.at('e')) == 5);
//        REQUIRE( int(letterFrequencyMap.at('l')) == 3);
//        REQUIRE( int(letterFrequencyMap.at('o')) == 2);
//
//        REQUIRE( int(letterFrequencyMap.at('W')) == 1);
//        REQUIRE( int(letterFrequencyMap.at('r')) == 2);
//        REQUIRE( int(letterFrequencyMap.at('d')) == 1);
//        REQUIRE( int(letterFrequencyMap.at('z')) == 1);
//        REQUIRE( int(letterFrequencyMap.at('i')) == 2);
//        REQUIRE( int(letterFrequencyMap.at('t')) == 2);
//        REQUIRE( int(letterFrequencyMap.at('a')) == 2);
//        REQUIRE( int(letterFrequencyMap.at('m')) == 2);
//
//        REQUIRE( int(letterFrequencyMap.at('x')) == 7);
//    }
//
//    SECTION("Test Huffman node < operator"){
//        HuffmanNode bigger = HuffmanNode('c',15);
//        HuffmanNode smaller = HuffmanNode('c',3);
//
//        REQUIRE( (bigger < smaller) == false );
//        REQUIRE( (smaller < bigger) == true );
//    }
//
//    SECTION("Test priority queue of Huffman Nodes"){
//        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;
//
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('x',7)));
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',5)));
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('h',1)));
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',15)));
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('y',4)));
//
//        shared_ptr<HuffmanNode> topOfQueue = priorityQueueTest.top();
//
//        REQUIRE( (*topOfQueue).getFrequency() == 1);
//
//        priorityQueueTest.pop();
//        REQUIRE((*priorityQueueTest.top()).getFrequency() == 4);
//
//        priorityQueueTest.pop();
//        REQUIRE((*priorityQueueTest.top()).getFrequency() == 5);
//
//        priorityQueueTest.pop();
//        REQUIRE((*priorityQueueTest.top()).getFrequency() == 7);
//
//        priorityQueueTest.pop();
//        REQUIRE((*priorityQueueTest.top()).getFrequency() == 15);
//
//    }
//
//    SECTION("Building the tree"){
//        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;
//
//                                                                                //  33----|
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('x',7)));//   |    17  ------ 10
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',6)));//   |     |      |     |
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('h',1)));//   |     |     |      5
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',15)));//  |     |    |     |    |
//        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('y',4)));  //15q   7x   6a   4y    1h
//
//        shared_ptr<HuffmanNode> testRootNode = huffmanTree.buildTree(priorityQueueTest);
//        REQUIRE((*testRootNode).getFrequency() == 33 ); //root should be the Total of all frequencies
//
//        REQUIRE(testRootNode.use_count() ==2);//should only have to ref counts- in this test and in the priority queue
//        //should only have reference pointer from the parent to left child -
//        // Important as this ensures that if root is deleted then the rest of tree deleted
//        REQUIRE(testRootNode->left.use_count() == 1);
//        REQUIRE(testRootNode->right.use_count() == 1);
//
//        SECTION("Test creating the Code Table"){
//            huffmanTree.buildCodeTableFromTree(testRootNode,"");
//
//            REQUIRE(huffmanTree.getCodeForLetter('q') == "0");
//            REQUIRE(huffmanTree.getCodeForLetter('x') == "10");
//            REQUIRE(huffmanTree.getCodeForLetter('h') == "1100");
//            REQUIRE(huffmanTree.getCodeForLetter('y') == "1101");
//            REQUIRE(huffmanTree.getCodeForLetter('a') == "111");
//
//        }
//        SECTION("Test the compress method"){
//            huffmanTree.buildCodeTableFromTree(testRootNode,"");
//            string compressedString = huffmanTree.compressStringWithHuffman("qxhyxxxhy"); //only letters from prev test
//            REQUIRE(compressedString == "0101100110110101011001101");
//
//        }
//
//    }
//
//    SECTION("Test the bitstream creation and output to file of the bitstream"){
//        //Creates bitstream file automatically
//        HuffmanTree bitTesTree = HuffmanTree("Hello Test blue black hitting hard hey handles honda hi","BitsTest.bin");
//        //Get the original compressed string from the huffman tree - string before written to any file
//        string compressedString = bitTesTree.compressStringWithHuffman("Hello Test blue black hitting hard hey handles honda hi");
//
//        //Will test to see if the bits retrieved from the Bitstream file are equal to the
//        //string representation the huffman tree created before
//        ifstream f("BitstreamBitsTest.bin", ios::binary | ios::in);
//        int numOfBitsInFile = 0;
//        char newline;
//        f.read((char*)&numOfBitsInFile, sizeof(numOfBitsInFile));
//        f.read((char*)&newline, sizeof(newline)); //Extracts new line character
//        char c;
//        string bitsFromBitStreamFile = "";
//        int bitsRetrieved = 0;
//        while (f.get(c) )
//        {
//            for (int i = 7; i >= 0; i--){
//                int bit = ((c >> i) & 1);
//                if (bitsRetrieved < numOfBitsInFile){
//                    bitsFromBitStreamFile = bitsFromBitStreamFile + to_string(bit);
//                    bitsRetrieved++;
//                }
//            }
//
//        }
//        REQUIRE(bitsFromBitStreamFile == compressedString);
//        f.close();
//    }
//    SECTION("Test reading in using bitstream file"){
//        HuffmanUtils util = HuffmanUtils();
//        string testStringToEncode = "Read in Test here test the"
//                "\n"
//                "sscsccc";
//        string outputFileName = "ReadingInTest.bin";
//        HuffmanTree *readInTestTree = new HuffmanTree(testStringToEncode,outputFileName);
//        string resultFromStream = (*readInTestTree).readInUsingBitstream(outputFileName);
//
//        REQUIRE(resultFromStream == testStringToEncode);
//        delete readInTestTree;
//    }
//    SECTION("Test the whole Huffman tree creation - start to finish"){
//
//        string wholeFile = huffmanUtils.readStringFromFile("TestDoc.txt");
//        HuffmanTree hf =  HuffmanTree(wholeFile,"outfile.bin");
//        string resultFromWholeFile = hf.readInUsingBitstream("outfile.bin");
//
//        REQUIRE(resultFromWholeFile == wholeFile);
//    }
//
//}
//TEST_CASE("Tests with a large text file") {
//    HuffmanTree huffmanTree = HuffmanTree();
//    HuffmanUtils huffmanUtils = HuffmanUtils();
//    string largeFile = huffmanUtils.readStringFromFile("TestDoc3.txt");
//
//    SECTION("Test the bitstream creation and output to file of the bitstream"){
//        //Creates bitstream file automatically
//        HuffmanTree bitTesTree = HuffmanTree(largeFile,"BitsTestLarge.bin");
//        //Get the original compressed string from the huffman tree - string before written to any file
//        string compressedString = bitTesTree.compressStringWithHuffman(largeFile);
//
//        //Will test to see if the bits retrieved from the Bitstream file are equal to the
//        //string representation the huffman tree created before
//        ifstream f("BitstreamBitsTestLarge.bin", ios::binary | ios::in);
//        int numOfBitsInFile = 0;
//        char newline;
//        f.read((char*)&numOfBitsInFile, sizeof(numOfBitsInFile));
//        f.read((char*)&newline, sizeof(newline)); //Extracts new line character
//        char c;
//        string bitsFromBitStreamFile = "";
//        int bitsRetrieved = 0;
//        while (f.get(c) )
//        {
//            for (int i = 7; i >= 0; i--){
//                int bit = ((c >> i) & 1);
//                if (bitsRetrieved < numOfBitsInFile){
//                    bitsFromBitStreamFile = bitsFromBitStreamFile + to_string(bit);
//                    bitsRetrieved++;
//                }
//            }
//
//        }
//        REQUIRE(bitsFromBitStreamFile == compressedString);
//        f.close();
//    }
//}