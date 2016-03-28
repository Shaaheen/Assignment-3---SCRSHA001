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
#include <memory>

using namespace std;
using namespace SCRSHA001;

TEST_CASE("Huffman tree building and destroying","[HuffmanTree]"){

    HuffmanTree huffmanTree = HuffmanTree();

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
        HuffmanNode bigger = HuffmanNode('c',15);
        HuffmanNode smaller = HuffmanNode('c',3);

        REQUIRE( (bigger < smaller) == false );
        REQUIRE( (smaller < bigger) == true );
    }

    SECTION("Test priority queue of Huffman Nodes"){
        priority_queue<shared_ptr<HuffmanNode>,vector<shared_ptr<HuffmanNode>>,HuffmanComparator> priorityQueueTest;

        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('x',7)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('a',5)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('h',1)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('q',15)));
        priorityQueueTest.push(shared_ptr<HuffmanNode>(new HuffmanNode('y',4)));

        shared_ptr<HuffmanNode> topOfQueue = priorityQueueTest.top();
        REQUIRE( (*topOfQueue).getFrequency() == 1);

    }

}