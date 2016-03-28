//
// Created by Shaaheen on 3/28/2016.
//

#include <array>
#include <fstream>
#include <unordered_map>
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

    //Function to write out the compressed string with associated code table values
    void HuffmanUtils::extractCompressedTextOut(const string &compressedString,const string &outName) const {
        char * bytesFromCompressed = (char *) compressedString.c_str();
        ofstream file(outName, std::ios::binary);
        file.write(bytesFromCompressed,compressedString.length());
        file.close();
    }

    //Function to create a file with the code table informaion stored in it
    void HuffmanUtils::createCodeTableFile(unordered_map<char, int> &letterFrequencyTable, const string &codeTableName, const unordered_map<char,string> &codeTable) const {
        ofstream codeTableFile;
        codeTableFile.open(codeTableName);
        codeTableFile <<letterFrequencyTable.size() <<endl;
        //Loop through letters found and print the corresponding code table value
        for (unordered_map<char,int>::iterator iterator = letterFrequencyTable.begin(); iterator != letterFrequencyTable.end(); ++iterator) {
            codeTableFile << iterator -> first << " " << codeTable.at(iterator->first) << endl;
        }
        codeTableFile.close();
    }

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



}

