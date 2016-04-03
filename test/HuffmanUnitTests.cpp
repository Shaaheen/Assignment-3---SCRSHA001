//
// Created by Shaaheen on 3/28/2016.
//
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "HuffmanUnitTests.h"
#include "../HuffmanTree.h"
#include "../HuffmanNode.h"
#include "../HuffmanUtils.h"
#include <unordered_map>
#include <queue>
#include <memory>

using namespace std;
using namespace SCRSHA001;

//Test case 1
TEST_CASE("Huffman tree building and destroying - all methods","[HuffmanTree]"){

    HuffmanTree huffmanTree = HuffmanTree();
    HuffmanUtils huffmanUtils = HuffmanUtils();

    SECTION("Testing letter frequency table"){
        //Test string
        string textFileTestCase = "Hello Worldzies hit the hammer heavy xxxxxxx";
        unordered_map<char,int> letterFrequencyMap = huffmanUtils.createLetterFrequencyTable(textFileTestCase);

        //Check if letter frequency table is correct
        REQUIRE( int(letterFrequencyMap.at('H')) == 1);
        REQUIRE( int(letterFrequencyMap.at('h')) == 4);
        REQUIRE( int(letterFrequencyMap.at('e')) == 5);
        REQUIRE( int(letterFrequencyMap.at('l')) == 3);
        REQUIRE( int(letterFrequencyMap.at('o')) == 2);

        REQUIRE( int(letterFrequencyMap.at('W')) == 1);
        REQUIRE( int(letterFrequencyMap.at('r')) == 2);
        REQUIRE( int(letterFrequencyMap.at('d')) == 1);
        REQUIRE( int(letterFrequencyMap.at('z')) == 1);
        REQUIRE( int(letterFrequencyMap.at('i')) == 2);
        REQUIRE( int(letterFrequencyMap.at('t')) == 2);
        REQUIRE( int(letterFrequencyMap.at('a')) == 2);
        REQUIRE( int(letterFrequencyMap.at('m')) == 2);

        REQUIRE( int(letterFrequencyMap.at('x')) == 7);
    }

    SECTION("Test Huffman node < operator"){
        HuffmanNode bigger = HuffmanNode('c',15);
        HuffmanNode smaller = HuffmanNode('c',3);

        REQUIRE( (bigger < smaller) == false );
        REQUIRE( (smaller < bigger) == true );
    }

    SECTION("Test priority queue of Huffman Nodes"){
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;

        //Sample nodes in queue
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('x',7)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',5)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('h',1)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',15)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('y',4)));

        //Check if priority of queue is correct
        shared_ptr<HuffmanNode> topOfQueue = priorityQueueTest.top();

        REQUIRE( (*topOfQueue).getFrequency() == 1);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 4);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 5);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 7);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 15);

    }

    SECTION("Building the tree"){
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;
                                                                                //  33----|
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('x',7)));//   |    17  ------ 10
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',6)));//   |     |      |     |
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('h',1)));//   |     |     |      5
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',15)));//  |     |    |     |    |
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('y',4)));  //15q   7x   6a   4y    1h

        shared_ptr<HuffmanNode> testRootNode = huffmanTree.buildTree(priorityQueueTest);
        REQUIRE((*testRootNode).getFrequency() == 33 ); //root should be the Total of all frequencies

        REQUIRE(testRootNode.use_count() ==2);//should only have to ref counts- in this test and in the priority queue
        //should only have reference pointer from the parent to left child -
        // Important as this ensures that if root is deleted then the rest of tree deleted
        REQUIRE(testRootNode->left.use_count() == 1);
        REQUIRE(testRootNode->right.use_count() == 1);

        SECTION("Test creating the Code Table"){
            huffmanTree.buildCodeTableFromTree(testRootNode,"");

            //Tests code table
            REQUIRE(huffmanTree.getCodeForLetter('q') == "0");
            REQUIRE(huffmanTree.getCodeForLetter('x') == "10");
            REQUIRE(huffmanTree.getCodeForLetter('h') == "1100");
            REQUIRE(huffmanTree.getCodeForLetter('y') == "1101");
            REQUIRE(huffmanTree.getCodeForLetter('a') == "111");

        }
        SECTION("Test the compress method"){
            //Tests whole compress method
            huffmanTree.buildCodeTableFromTree(testRootNode,"");
            string compressedString = huffmanTree.compressStringWithHuffman("qxhyxxxhy"); //only letters from prev test
            REQUIRE(compressedString == "0101100110110101011001101");

        }

    }

    //LAST 10% Test - Tests that the outputted bit packed file is what it should be
    SECTION("Test the bitstream creation and output to file of the bitstream"){
        //Creates bitstream file automatically
        HuffmanTree bitTesTree = HuffmanTree("Hello Test blue black hitting hard hey handles honda hi","BitsTest.bin");
        //Get the original compressed string from the huffman tree - string before written to any file
        string compressedString = bitTesTree.compressStringWithHuffman("Hello Test blue black hitting hard hey handles honda hi");

        //Will test to see if the bits retrieved from the Bitstream file are equal to the
        //string representation the huffman tree created before
        ifstream f("BitstreamBitsTest.bin", ios::binary | ios::in);
        int numOfBitsInFile = 0;
        char newline;
        f.read((char*)&numOfBitsInFile, sizeof(numOfBitsInFile));
        f.read((char*)&newline, sizeof(newline)); //Extracts new line character
        char c;
        string bitsFromBitStreamFile = "";
        int bitsRetrieved = 0;
        while (f.get(c) )
        {
            for (int i = 7; i >= 0; i--){
                int bit = ((c >> i) & 1);
                if (bitsRetrieved < numOfBitsInFile){
                    bitsFromBitStreamFile = bitsFromBitStreamFile + to_string(bit);
                    bitsRetrieved++;
                }
            }

        }
        REQUIRE(bitsFromBitStreamFile == compressedString);
        f.close();
    }
    //Last 10% Test that the reading in a bitstream file works correctly
    SECTION("Test reading in using bitstream file"){
        HuffmanUtils util = HuffmanUtils();
        string testStringToEncode = "Read in Test here test the"
                "\nfnjvf"
                "sscsccc";
        string outputFileName = "ReadingInTest.bin";
        HuffmanTree *readInTestTree = new HuffmanTree(testStringToEncode,outputFileName);
        string resultFromStream = (*readInTestTree).readInUsingBitstream(outputFileName);

        REQUIRE(resultFromStream == testStringToEncode);
        delete readInTestTree;
    }
    SECTION("Test the whole Huffman tree creation - start to finish"){

        string wholeFile = huffmanUtils.readStringFromFile("TestDoc.txt");
        HuffmanTree hf =  HuffmanTree(wholeFile,"outfile.bin");
        string resultFromWholeFile = hf.readInUsingBitstream("outfile.bin");

        REQUIRE(resultFromWholeFile == wholeFile);
    }

}
TEST_CASE("Tests with a large text file") {
    HuffmanTree huffmanTree = HuffmanTree();
    HuffmanUtils huffmanUtils = HuffmanUtils();
    string largeFile = huffmanUtils.readStringFromFile("TestDoc3.txt");

    SECTION("Test the bitstream creation and output to file of the bitstream"){
        //Creates bitstream file automatically
        HuffmanTree bitTesTree = HuffmanTree(largeFile,"BitsTestLarge.bin");
        //Get the original compressed string from the huffman tree - string before written to any file
        string compressedString = bitTesTree.compressStringWithHuffman(largeFile);

        //Will test to see if the bits retrieved from the Bitstream file are equal to the
        //string representation the huffman tree created before
        ifstream f("BitstreamBitsTestLarge.bin", ios::binary | ios::in);
        int numOfBitsInFile = 0;
        char newline;
        f.read((char*)&numOfBitsInFile, sizeof(numOfBitsInFile));
        f.read((char*)&newline, sizeof(newline)); //Extracts new line character
        char c;
        string bitsFromBitStreamFile = "";
        int bitsRetrieved = 0;
        while (f.get(c) )
        {
            for (int i = 7; i >= 0; i--){
                int bit = ((c >> i) & 1);
                if (bitsRetrieved < numOfBitsInFile){
                    bitsFromBitStreamFile = bitsFromBitStreamFile + to_string(bit);
                    bitsRetrieved++;
                }
            }

        }
        REQUIRE(bitsFromBitStreamFile == compressedString);
        f.close();
    }
}
TEST_CASE("Test 2 of the whole Huffman Tree "){
    HuffmanUtils huffmanUtils = HuffmanUtils();
    string wholeFile = huffmanUtils.readStringFromFile("TestDoc2.txt");
    HuffmanTree hf =  HuffmanTree(wholeFile,"outfile.bin");
    string resultFromWholeFile = hf.readInUsingBitstream("outfile.bin");

    REQUIRE(resultFromWholeFile == wholeFile);
}

//Test case 2
TEST_CASE("Another test case to test the functions of the Huffman Tree","[HuffmanTree]"){

    HuffmanTree huffmanTree = HuffmanTree();
    HuffmanUtils huffmanUtils = HuffmanUtils();

    SECTION("Testing letter frequency table"){
        //Test string
        string textFileTestCase = "Second test sec time so super solid test super sssss .. ttt";
        unordered_map<char,int> letterFrequencyMap = huffmanUtils.createLetterFrequencyTable(textFileTestCase);

        //Check if letter frequency table is correct
        REQUIRE( int(letterFrequencyMap.at('S')) == 1);
        REQUIRE( int(letterFrequencyMap.at('s')) == 12);
        REQUIRE( int(letterFrequencyMap.at('e')) == 7);
        REQUIRE( int(letterFrequencyMap.at('t')) == 8);
    }

    SECTION("Test Huffman node < operator"){
        HuffmanNode bigger = HuffmanNode('h',15);
        HuffmanNode smaller = HuffmanNode('k',3);

        REQUIRE( (bigger < smaller) == false );
        REQUIRE( (smaller < bigger) == true );
    }

    SECTION("Test priority queue of Huffman Nodes"){
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;

        //Sample nodes in queue
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('j',7)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('r',5)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',1)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('k',15)));

        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('b',4)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',2)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('z',10)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('u',9)));

        //Check if priority of queue is correct
        shared_ptr<HuffmanNode> topOfQueue = priorityQueueTest.top();

        REQUIRE( (*topOfQueue).getFrequency() == 1);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 2);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 4);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 5);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 7);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 9);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 10);

        priorityQueueTest.pop();
        REQUIRE((*priorityQueueTest.top()).getFrequency() == 15);

    }

    SECTION("Building the tree"){
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;
        //  33----|
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('x',7)));//   |    17  ------ 10
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',6)));//   |     |      |     |
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('h',1)));//   |     |     |      5
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',15)));//  |     |    |     |    |
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('y',4)));  //15q   7x   6a   4y    1h

        shared_ptr<HuffmanNode> testRootNode = huffmanTree.buildTree(priorityQueueTest);
        REQUIRE((*testRootNode).getFrequency() == 33 ); //root should be the Total of all frequencies

        REQUIRE(testRootNode.use_count() ==2);//should only have to ref counts- in this test and in the priority queue
        //should only have reference pointer from the parent to left child -
        // Important as this ensures that if root is deleted then the rest of tree deleted
        REQUIRE(testRootNode->left.use_count() == 1);
        REQUIRE(testRootNode->right.use_count() == 1);

        SECTION("Test creating the Code Table"){
            huffmanTree.buildCodeTableFromTree(testRootNode,"");

            //Tests code table
            REQUIRE(huffmanTree.getCodeForLetter('q') == "0");
            REQUIRE(huffmanTree.getCodeForLetter('x') == "10");
            REQUIRE(huffmanTree.getCodeForLetter('h') == "1100");
            REQUIRE(huffmanTree.getCodeForLetter('y') == "1101");
            REQUIRE(huffmanTree.getCodeForLetter('a') == "111");

        }
        SECTION("Test the compress method"){
            //Tests whole compress method
            huffmanTree.buildCodeTableFromTree(testRootNode,"");
            string compressedString = huffmanTree.compressStringWithHuffman("qxhyxxxhy"); //only letters from prev test
            REQUIRE(compressedString == "0101100110110101011001101");

        }

    }

    //LAST 10% Test - Tests that the outputted bit packed file is what it should be
    SECTION("Test the bitstream creation and output to file of the bitstream"){
        //Creates bitstream file automatically
        HuffmanTree bitTesTree = HuffmanTree("Testing the extract method of the bitstream again test test","BitsTest2.bin");
        //Get the original compressed string from the huffman tree - string before written to any file
        string compressedString = bitTesTree.compressStringWithHuffman("Testing the extract method of the bitstream again test test");

        //Will test to see if the bits retrieved from the Bitstream file are equal to the
        //string representation the huffman tree created before
        ifstream f("BitstreamBitsTest2.bin", ios::binary | ios::in);
        int numOfBitsInFile = 0;
        char newline;
        f.read((char*)&numOfBitsInFile, sizeof(numOfBitsInFile));
        f.read((char*)&newline, sizeof(newline)); //Extracts new line character
        char c;
        string bitsFromBitStreamFile = "";
        int bitsRetrieved = 0;
        while (f.get(c) )
        {
            for (int i = 7; i >= 0; i--){
                int bit = ((c >> i) & 1);
                if (bitsRetrieved < numOfBitsInFile){
                    bitsFromBitStreamFile = bitsFromBitStreamFile + to_string(bit);
                    bitsRetrieved++;
                }
            }

        }
        REQUIRE(bitsFromBitStreamFile == compressedString);
        f.close();
    }
    //Last 10% Test that the reading in a bitstream file works correctly
    SECTION("Test reading in using bitstream file"){
        HuffmanUtils util = HuffmanUtils();
        string testStringToEncode = "bvdvbv9fhf9 bf 9fb fdj fd io.;'.';/.';.';.;';';dcjdkc dcd jkc";
        string outputFileName = "ReadingInTest2.bin";
        HuffmanTree *readInTestTree = new HuffmanTree(testStringToEncode,outputFileName);
        string resultFromStream = (*readInTestTree).readInUsingBitstream(outputFileName);

        REQUIRE(resultFromStream == testStringToEncode);
        delete readInTestTree;
    }

}