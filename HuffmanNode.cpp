#include <iostream>
//#include <memory>
#include "HuffmanNode.h"

using namespace std;

void HuffmanNode::log(const char *msg) {
    cout << "[" << this << "]" << msg << endl;
}

HuffmanNode::HuffmanNode(char letter, int frequency): cLetter(letter), iFrequency(frequency) {
    //log("constructor");
}

HuffmanNode::~HuffmanNode() {
    //log("destructor");
    cLetter = 0;
    iFrequency = 0;
    left = nullptr;
    right = nullptr;
}
//move constructor
HuffmanNode::HuffmanNode(HuffmanNode &&other):cLetter(move(other.cLetter)), iFrequency(other.iFrequency), left(move(other.left)), right(move(other.right)) {
    //log("move constructor");
}
//copy constructor
HuffmanNode::HuffmanNode(const HuffmanNode &other):cLetter(other.cLetter), iFrequency(other.iFrequency), left(other.left), right(other.right) {
    //log("copy constructor");
}
//move assignment operator
HuffmanNode& HuffmanNode::operator=(HuffmanNode &&rhs) {
    //log("move assignment operator");
    if (this!=&rhs){
        cLetter = move(rhs.getLetter());
        iFrequency = rhs.getFrequency();

        left.reset();
        right.reset();

        left = move(rhs.left);
        right = move(rhs.right);
    }
    return *this;

}
//copy assignment operator
HuffmanNode& HuffmanNode::operator=(const HuffmanNode &rhs) {
    //log("copy assignment operator");
    if (this!=&rhs){
        cLetter = rhs.cLetter;
        iFrequency = rhs.iFrequency;

        left.reset();
        right.reset();

        left = rhs.left;
        right = rhs.right;
    }
    return *this;
}
//getters
char HuffmanNode::getLetter() const {
    return cLetter;
}

int HuffmanNode::getFrequency() const{
    return iFrequency;
}

std::shared_ptr<HuffmanNode> HuffmanNode::getLeft() const {
    return left;
}

std::shared_ptr<HuffmanNode> HuffmanNode::getRight() const {
    return right;
}

void HuffmanNode::setLeftAndRight(HuffmanNode &l, HuffmanNode &r) {
    left = make_shared<HuffmanNode>(l);
    right = make_shared<HuffmanNode>(r);
}
