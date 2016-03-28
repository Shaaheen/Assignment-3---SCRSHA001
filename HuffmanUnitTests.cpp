//
// Created by Shaaheen on 3/28/2016.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "HuffmanUnitTests.h"
#include "HuffmanTree.h"
#include "HuffmanNode.h"
#include <unordered_map>
#include <queue>

using namespace std;

bool compare(const SCRSHA001::HuffmanNode& a,const SCRSHA001::HuffmanNode & b){
    return (a < b) ;
}

TEST_CASE("Huffman tree building and destroying","[HuffmanTree]"){

    SCRSHA001::HuffmanTree huffmanTree = SCRSHA001::HuffmanTree();

    SECTION("Testing letter frequency table"){
        string textFileTestCase = "Hello Worldzies hit the hammer heavy xxxxxxx";
        unordered_map<char,int> letterFrequencyMap = huffmanTree.createLetterFrequencyTable(textFileTestCase);

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
        SCRSHA001::HuffmanNode bigger = SCRSHA001::HuffmanNode('c',15);
        SCRSHA001::HuffmanNode smaller = SCRSHA001::HuffmanNode('c',3);

        REQUIRE( (bigger < smaller) == false );
        REQUIRE( (smaller < bigger) == true );
    }

    SECTION("Test priority queue of Huffman Nodes"){
        priority_queue< SCRSHA001::HuffmanNode,vector<SCRSHA001::HuffmanNode>,function<bool(const SCRSHA001::HuffmanNode,const SCRSHA001::HuffmanNode)> > priorityQueueTest(compare);
        priorityQueueTest.push(SCRSHA001::HuffmanNode('x',1));
        priorityQueueTest.push(SCRSHA001::HuffmanNode('a',5));
        SCRSHA001::HuffmanNode topOfQueue = priorityQueueTest.top();
        REQUIRE( topOfQueue.getFrequencey() == 1);

    }

}