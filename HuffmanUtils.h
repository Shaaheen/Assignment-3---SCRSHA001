//
// Created by Shaaheen on 3/28/2016.
//

#ifndef ASSIGNMENT_3_SCRSHA001_HUFFMANUTILS_H
#define ASSIGNMENT_3_SCRSHA001_HUFFMANUTILS_H

#include <unordered_map>
namespace SCRSHA001{
    class HuffmanUtils {
        public:

            std::unordered_map<char, int> createLetterFrequencyTable(const std::string &toEncode) const;

            void createCodeTableFile(std::unordered_map<char, int> &letterFrequencyTable, const std::string &codeTableName,
                                     const std::unordered_map<char, std::string> &codeTable) const;

            std::string readStringFromFile(std::string fileName);

            void extractCompressedTextOut(const std::string &compressedString, const std::string &outName) const;
    };
}




#endif //ASSIGNMENT_3_SCRSHA001_HUFFMANUTILS_H
