#ifndef _HUFFMANNODE_H
#define _HUFFMANNODE_H


#include <memory>

class HuffmanNode {
private:
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
    char cLetter;
    int iFrequency;

    void log(const char* msg);
public:
    //default constructor
    HuffmanNode(char letter, int frequency);
    //destructor
   ~HuffmanNode();
    //copy constructor
    HuffmanNode(const HuffmanNode& other);
    //move constructor
    HuffmanNode(HuffmanNode&& other);
    //copy assignment operator
    HuffmanNode& operator=(const HuffmanNode& rhs);
    //move assignment operator
    HuffmanNode& operator=(HuffmanNode&& rhs);

    //getters
    char getLetter() const;
    int getFrequency() const;
    std::shared_ptr<HuffmanNode> getLeft() const;
    std::shared_ptr<HuffmanNode> getRight() const;

    //setters
    void setLeftAndRight(HuffmanNode &l, HuffmanNode &r);
};


#endif
