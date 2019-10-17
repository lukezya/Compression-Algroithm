#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "HuffmanTree.h"
#include "HuffmanNode.h"

using namespace std;

//priority queue compare
bool operator<(const HuffmanNode& lhs, const HuffmanNode& rhs){
    return lhs.getFrequency() > rhs.getFrequency();
};

bool compare::operator()(const HuffmanNode& a, const HuffmanNode& b) const{
    return a < b;
}

//build frequency count of char from inputfile
unordered_map<char,int>buildFreq(string fInput){
    //keeping count of letter frequency
    unordered_map<char,int> letterFreq;
    //read input file - get frequency count of letters
    cout << "Building map for frequency count of letters for "+fInput+ " ..." <<endl;
    ifstream ifsInput(fInput);

    if (!ifsInput){
        //cerr << "Opening " << headerFilename << " failed :(" << endl;
        cout << "Opening " << fInput << " failed :(" << endl;
    } else {
        //read in char by char
        char cIn;
        while (ifsInput>>noskipws>>cIn){
            letterFreq[cIn]++;
        }
        ifsInput.close();
    }

    /*for (auto &e:letterFreq) {
        cout << e.first << ","<<e.second<<endl;
    }*/
    cout << "Finished building frequency count of letters for "+fInput+"."<<endl;

    return letterFreq;
};

//constructor
HuffmanTree::HuffmanTree(unordered_map<char, int> &FreqCount) {
    //load letters with frequency into priority queue
    priority_queue<HuffmanNode, vector<HuffmanNode>, compare> letterQueue;

    cout << "Creating priority queue to assist in building tree..." << endl;

    //zz
    for (auto &e:FreqCount) {
        HuffmanNode addNode(e.first, e.second);
        letterQueue.push(addNode);
    }

    cout << "Finished building priority queue." << endl;
    cout << "Building tree..." << endl;
    //build tree with priority queue
    while(letterQueue.size()>1){
        //pop() calls removed elements destructor
        HuffmanNode left = letterQueue.top();
        letterQueue.pop();
        HuffmanNode right = letterQueue.top();
        letterQueue.pop();
        //left and right are copied
        int newFrequency = left.getFrequency()+right.getFrequency();
        HuffmanNode combine(0, newFrequency);
        //reponsibility is given to shared pointers, won't delete left and right
        combine.setLeftAndRight(left, right);
        letterQueue.push(combine);
    }

    //construct tree
    root = make_shared<HuffmanNode>(letterQueue.top());
    letterQueue.pop();

    cout << "Finished building tree." << endl;
    //queue now empty

}
//destructor
HuffmanTree::~HuffmanTree() {
    //root.reset();
    root = nullptr;
}
//copy constructor
HuffmanTree::HuffmanTree(const HuffmanTree &other):root(other.root) {

}
//move constructor
HuffmanTree::HuffmanTree(HuffmanTree &&other):root(move(other.root)) {

}
//copy assignment operator
HuffmanTree& HuffmanTree::operator=(const HuffmanTree &rhs) {
    if (this!=&rhs){
        root.reset();
        root = rhs.root;
    }
    return *this;
}
//move assignment operator
HuffmanTree& HuffmanTree::operator=(HuffmanTree &&rhs) {\
    if (this!=&rhs){
        root.reset();
        root = move(rhs.root);
    }

    return *this;
}

void HuffmanTree::inOrder() {
    cout << "Building code table for letters..." << endl;
    string sCode="";
    inOrder(root, sCode);
    cout << "Finished building code table." << endl;
}

void HuffmanTree::inOrder(std::shared_ptr<HuffmanNode> hn, string sCode) {
    //construct string code for each branching
    string sLeft = sCode + "0";
    string sRight = sCode + "1";

    //if next not null
    if (hn->getLeft() && hn->getRight()){
        inOrder(hn->getLeft(), sLeft);
        inOrder(hn->getRight(), sRight);
    } else {
        //if next is null - hn is leaf with string code sCode
        codeTable[hn->getLetter()] = sCode;
    }

}

//see contents of char with string code
void HuffmanTree::printCodeTable(){
    for (auto &it:codeTable) {
        cout<<it.first<<","<<it.second<<endl;
    }
}

//outputs code table to file
void HuffmanTree::writeCodeTableToFile(string outFileName) {
    string outTableFile = outFileName + ".hdr";
    ofstream ofsTable(outTableFile);
    ofsTable << codeTable.size()<<endl;
    for (auto &it:codeTable) {
        ofsTable<<it.first<<"|"<<it.second<<endl;
    }

    ofsTable.close();
    cout << "Wrote code table to "+outTableFile+" file." << endl;
}

//compress inputfile and output to outputfile
void HuffmanTree::compressFile(std::string inputFile, std::string outputFile) {
    cout << "Compressing "+inputFile +"..."<< endl;
    string sBuffer = "";
    //read input file
    cout << "Buffering..." << endl;
    ifstream ifsInput(inputFile);

    if (!ifsInput){
        //cerr << "Opening " << inputFile << " failed :(" << endl;
        cout << "Opening " << inputFile << " failed :(" << endl;
    } else {
        //read in char by char and lookup string code
        char cIn;
        while (ifsInput>>noskipws>>cIn){
            auto letterSearch = codeTable.find(cIn);
            if(letterSearch != codeTable.end()) {
                sBuffer = sBuffer + letterSearch->second;
            }
            else {
                cout << cIn << "Not found\n";
            }
        }
        ifsInput.close();
    }

    //cout<<sBuffer<<endl;
    //extract c_str() from string buffer and write to file
    ofstream ofsOutput(outputFile);//, ios::binary);
    ofsOutput.write(sBuffer.c_str(), sBuffer.size());

    ofsOutput.close();
    cout << "Wrote string buffer to "+outputFile+"."<<endl;
    //extra credit, convert to actual bit stream and output to binary file
    bitpack(sBuffer, outputFile);

}

//converting to actual bit stream and outputting to binary file
void HuffmanTree::bitpack(string sBuffer, string outputFile) {
    //extra credit
    //sBuffer to actual bit stream
    cout << "Converting string buffer to actual bit stream..."<<endl;
    int arraySize = sBuffer.length()/8+(sBuffer.length()%8? 1:0);
    int realSize = sBuffer.length();
    //make sBuffer divisible by 8
    int addTimes = 8-(sBuffer.length()%8);

    for (int j = 0;j<addTimes;j++){
        sBuffer = sBuffer+"0";
    }
    int tempSize = sBuffer.length();
    unsigned char bytes[arraySize];
    int iCounter = 0;
    while (sBuffer.length()>0){
        unsigned char byte = 0;
        for( int i = 0; i < 8; ++i )
            if( sBuffer[i] == '1' ) byte |= 1 << (7-i);

        bytes[iCounter] = byte;
        iCounter++;
        sBuffer = sBuffer.substr(8);
    }
    cout << "Finished converting to actual bit stream." << endl;
    //got byte array

    string binaryFilename = outputFile+".raw";

    ofstream ofsExtra(binaryFilename,ios::binary);
    ofsExtra.write(reinterpret_cast<char *>(&realSize), sizeof(int));
    ofsExtra.write(reinterpret_cast<const char *>(bytes), arraySize);
    ofsExtra.flush();
    ofsExtra.close();

    cout << "Finished writing to "+binaryFilename + "." <<endl;

}

//read in binary file and get orginal message from binary file
string HuffmanTree::bitunpack(std::string filename) {
    //read in
    cout << "Unpacking bits of file - "+filename+"..."<<endl;
    int iBitSize;
    ifstream ifsBinary(filename, ios::binary);
    ifsBinary.read(reinterpret_cast<char *>(&iBitSize), sizeof(int));
    //create array to store bytes
    int iArraySize = iBitSize/8+(iBitSize%8? 1:0);
    int iRealSize = (8-(iBitSize%8))+iBitSize;
    unsigned char bytesRead[iArraySize];
    ifsBinary.read(reinterpret_cast<char *>(bytesRead), iArraySize);
    ifsBinary.close();
    //loop through array and read bits
    string sBuffer = "";
    for (int i=0;i<iArraySize;i++){
        bitset<8> bs (bytesRead[i]);
        sBuffer += bs.to_string();
    }
    cout << "Finished unpacking bits."<<endl;
    cout << "Deciphering bits with code table..."<<endl;
    //create another map with the keys and values swapped
    unordered_map<string, char> charTable;
    for (auto &it:codeTable) {
        charTable[it.second] = it.first;
    }
    string sDecode="";
    string sDecipher = "";
    for (int j = 0;j<iBitSize;j++){
        sDecipher+=sBuffer[j];
        auto search = charTable.find(sDecipher);
        if(search != charTable.end()) {
            sDecipher="";
            sDecode+=search->second;
        }
    }
    cout << "Finished deciphering, printing out deciphered message/text:"<<endl;
    return sDecode;

}

/*bool HuffmanTree::getBit(unsigned char byte, int position) {
    return (byte >> position) & 0x1;
}*/

//testing cases
//get height of binary tree
int HuffmanTree::getHeight() {
    return getHeight(root);
}

int HuffmanTree::getHeight(std::shared_ptr<HuffmanNode> hn) {

    if (hn.get()== nullptr){
        return -1;
    }
    int iLeft = getHeight(hn->getLeft());
    int iRight = getHeight(hn->getRight());
    int iMax = max(iLeft, iRight);
    return 1+iMax;
}

//get size of binary tree
int HuffmanTree::getSize() {
    return getSize(root);
}

int HuffmanTree::getSize(std::shared_ptr<HuffmanNode> hn) {
    if (hn.get()==nullptr){
        return 0;
    } //else {
        //iCount++;
        return 1+getSize(hn->getLeft())+getSize(hn->getRight());
   // }
}

std::shared_ptr<HuffmanNode> HuffmanTree::getRoot() const {
    return root;
}

std::unordered_map<char, std::string> HuffmanTree::getCodeTable() const {
    return codeTable;
}
