//
// Created by Shaaheen on 3/28/2016.
//

#include <array>
#include <fstream>
#include <unordered_map>
#include <bitset>
#include <iostream>
#include "HuffmanUtils.h"
#include "HuffmanTree.h"

using namespace std;

namespace SCRSHA001{

    string HuffmanUtils::readStringFromFile(string fileName){
        ifstream t(fileName);
        string toEncodeFileText((istreambuf_iterator<char>(t)),
                        istreambuf_iterator<char>());
        t.close();
        return toEncodeFileText;
    }

    //Function to write out the compressed huffman encoded string with associated code table values
    void HuffmanUtils::extractCompressedTextOut(const string &compressedString,const string &outName) const {
        char * bytesFromCompressed = (char *) compressedString.c_str();
        ofstream file(outName, std::ios::binary);
        file.write(bytesFromCompressed,compressedString.length());
        file.close();
    }

    //Function to create a file with the code table information stored in it
    void HuffmanUtils::createCodeTableFile(unordered_map<char, int> &letterFrequencyTable, const string &codeTableName, const unordered_map<char,string> &codeTable) const {
        ofstream codeTableFile;
        codeTableFile.open(codeTableName);
        codeTableFile <<letterFrequencyTable.size() <<endl; //Header field
        //Loop through letters found and print the corresponding code table value
        for (unordered_map<char,int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            codeTableFile << iterator -> first << " " << codeTable.at(iterator->first) << endl;
        }
        codeTableFile.close();
    }

    //Function to create backwards code table to assist in reading a encoded file - Bit codes lead to char values
    unordered_map<string,char> HuffmanUtils::createCodeToCharTable(unordered_map<char, int> &letterFrequencyTable, const unordered_map<char,string> &codeTable) const
    {
        unordered_map<string,char> codeToCharTable;
        //Loop through letters found and set the corresponding code table value to char value
        for (unordered_map<char,int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            codeToCharTable.insert({codeTable.at(iterator->first),iterator->first}); //Bitstream code key and char value
        }
        return codeToCharTable;
    };

    unordered_map<char, int> HuffmanUtils::createLetterFrequencyTable(const string &toEncode) const {

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

    /*
     * Function to take in a string representation of bits and join the bits together to a byte
     * Store those bytes in a buffer and then write buffer to binary outfile
    */
    int HuffmanUtils::extractUsingBitstream(string &compressedString,const string &outFileName) const {
        ofstream stream("Bitstream" + outFileName, ios_base::binary);

        int numberOfBits = compressedString.size();
        int numberOfBytesCreated = (numberOfBits/8) + (numberOfBits%8 ? 1:0); //Formula from assignment brief
        char newLine = '\n';
        stream.write((const char *) &numberOfBits, sizeof(int)); //Prints number of bits in file in header
        stream.write((const char *) &newLine,sizeof(newLine)); //New line

        unsigned int getBitsFrom = 0;
        for (int i=0;  i < numberOfBytesCreated; i++) {
            if ((getBitsFrom+8) >numberOfBits){ //If last byte needs more bits from compressedString then fill with 0's
                int diff = (getBitsFrom+8) - numberOfBits;
                for (int j = 0; j < diff; ++j) {
                    compressedString = compressedString + "0"; //Add 0's that will be discarded just to make a whole byte now
                }

            }
            bitset<8> bitstream (compressedString.substr(getBitsFrom,getBitsFrom+8)); //Get bitstream from string representation
            //bit string -> bit set -> long value -> char
            //"10101111" -> {1,0,1,0,1,1,1,1} -> long representation -> char representation
            char byteA = (char) bitstream.to_ulong();//Get char value(byte value) of bitstream to represent bits as a byte together
            stream.write((const char *) &byteA, 1); //Write that byte straight to file
            getBitsFrom = getBitsFrom + 8;
        }
        stream.close();
        return numberOfBytesCreated;
    }



}

