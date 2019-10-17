#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <queue>
#include "HuffmanNode.h"
#include "HuffmanTree.h"

using namespace std;

int main(int argc, char * argv[]) {
    //huffencode <inputFile> <output_file>
    //get command line arguments
    string sInputFile = string(argv[1]);
    string sOutputFile = string(argv[2]);

    //keeping count of letter frequency
    unordered_map<char,int> letterFreq = buildFreq(sInputFile);

    //construct tree with frequency count and help of priority queue
    HuffmanTree *hTree = new HuffmanTree(letterFreq);
    //construct code table
    hTree->inOrder();
    //hTree->printCodeTable();
    //output code table to file
    hTree->writeCodeTableToFile(sOutputFile);
    //compress file and write to output file, also convert to actual bit stream and write to binary file <outputfile>.raw
    hTree->compressFile(sInputFile, sOutputFile);
    //unpack given binary file for original message
    string sDecode = hTree->bitunpack(sOutputFile+".raw");
    cout << sDecode << endl;

    delete hTree;

    return 0;
}