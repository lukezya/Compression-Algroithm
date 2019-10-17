#ifndef _HUFFMANTREE_H
#define _HUFFMANTREE_H


#include <memory>
#include <unordered_map>
#include <string>
#include "HuffmanNode.h"

bool operator<(const HuffmanNode& lhs, const HuffmanNode& rhs);
std::unordered_map<char,int>buildFreq(std::string fInput);

struct compare{
    bool operator()(const HuffmanNode& a, const HuffmanNode& b) const;
};

class HuffmanTree {
private:
    //tree
    std::shared_ptr<HuffmanNode> root;
    //code table
    std::unordered_map<char, std::string> codeTable;
public:
    //constructor
    HuffmanTree(std::unordered_map<char,int> &FreqCount);
    //destructor
    ~HuffmanTree();

    //copy constructor
    HuffmanTree(const HuffmanTree& other);
    //move constructor
    HuffmanTree(HuffmanTree&& other);
    //copy assignment operator
    HuffmanTree&operator=(const HuffmanTree& rhs);
    //move assignment operator
    HuffmanTree&operator=(HuffmanTree&& rhs);

    //inorder traversal
    void inOrder();
    void inOrder(std::shared_ptr<HuffmanNode> hn, std::string sCode);

    void printCodeTable();
    //write code table to outputfile
    void writeCodeTableToFile(std::string outFileName);
    //compress inputfile and write to output file
    void compressFile(std::string inputFile, std::string outputFile);
    //convert to actual bit stream and write to binary file
    void bitpack(std::string sBuffer, std::string outputFile);
    //unpack bits of binary file and get original message
    std::string bitunpack(std::string filename);
    //bool getBit(unsigned char byte, int position);

    //testing purposes
    //height of binary tree
    int getHeight();
    int getHeight(std::shared_ptr<HuffmanNode> hn);
    //size of binary tree
    int getSize();
    int getSize(std::shared_ptr<HuffmanNode> hn);
    std::shared_ptr<HuffmanNode> getRoot() const;
    std::unordered_map<char, std::string> getCodeTable() const;

};


#endif
