Hey :)
Note* : Have completed the last 10% by creating and reading bitstream

To run main program: 
    1) Go into outer directory from terminal
    2) Run "make" command in terminal to compile the program
    3) run ./huffencode <inputFile> <output file> command from terminal
	4) Program should create a new files 
		-output file with the provided output filename
		-a bit packed file called "Bitstream" + output filename
		-a code table of the created huffman tree called output filename + "CodeTable.txt"
	5) Run "make clean" to clear all .o files, .bin files, any CodeTable.txt files and the main program
	
eg: ./huffencode TestDoc2 outputFile

To run unit test program: 
    1) Go into test directory from terminal
    2) Run "make" command in terminal to compile the program
    3) run ./huffTest command from terminal
	4) A large number of files should be produced as a result of running tests 
		- info will be displayed from program on this
	5) Run "make clean" to clear all created test files, .o files and the unit test program
	
eg: ./huffTest
	
HuffmanTree class:
	Main class holding the root node, code table and letter frequency
	Will take in a string and build the huffman tree around that
	
HuffmanUtils class:
	A utility class to provide functions for the HuffmanTree class
	
HuffmanNode class:
	A Node class to represent a node in the huffman tree
	Holds letter, frequency of letter and links to children nodes
	
HuffmanUnitTests:
	Class that house all the unit tests of the HuffmanTree class
	