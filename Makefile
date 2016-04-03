#Makefile for compiling work
#(C) Benjamin Hugo, 2015
#You are free to modify and reuse this in your own practicals
#This file is in the public domain

CPP=g++
CPPFLAGS=-std=c++11
EXE_NAME=huffencode
#define a generic rule: to go from .cpp to .o files make should invoke the c++ compiler
#the syntax tells make to invoke the compiler without linking (-c), outputting a .o file reading a .cpp file, additionally specifying flags

$(EXE_NAME): main.o HuffmanTree.o  HuffmanUtils.o HuffmanNode.o
	$(CPP) -o $(EXE_NAME) main.o HuffmanTree.o  HuffmanUtils.o HuffmanNode.o $(CPPFLAGS) 

HuffmanTree.o : HuffmanUtils.h HuffmanTree.h HuffmanTree.cpp
	$(CPP) -c -o HuffmanTree.o HuffmanTree.cpp $(CPPFLAGS)
	
HuffmanNode.o : HuffmanNode.h HuffmanNode.cpp
	$(CPP) -c -o HuffmanNode.o HuffmanNode.cpp $(CPPFLAGS)
	
HuffmanUtils.o : HuffmanUtils.h HuffmanUtils.cpp
	$(CPP) -c -o HuffmanUtils.o HuffmanUtils.cpp $(CPPFLAGS)

main.o : HuffmanTree.h HuffmanUtils main.cpp
	$(CPP) -c -o main.o main.cpp $(CPPFLAGS)

#Never submit binaries to your git repo or vula, so create a rule for cleaning up the binary objects just leaving your source code behind
clean:
	@rm *.o huffencode
