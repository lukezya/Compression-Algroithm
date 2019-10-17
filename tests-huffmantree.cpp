#include <string>
#include <unordered_map>
#include <fstream>

#include "catch.hpp"

#include "HuffmanTree.h"

using namespace std;

TEST_CASE("Counting frequency of letters","[frequency counting]"){
  string sInputFile = "suhdude.txt";
  unordered_map<char,int> letterFreq = buildFreq(sInputFile);
  //check if map contains correct frequencies with some letters
  auto search = letterFreq.find('f');
  REQUIRE(search->second==1);
  search = letterFreq.find('?');
  REQUIRE(search->second==2);
  search = letterFreq.find('h');
  REQUIRE(search->second==4);
  search = letterFreq.find(' ');
  REQUIRE(search->second==14);
  search = letterFreq.find('s');
  REQUIRE(search->second==5);
  search = letterFreq.find('t');
  REQUIRE(search->second==7);
  search = letterFreq.find('i');
  REQUIRE(search->second==7);
  search = letterFreq.find('e');
  REQUIRE(search->second==4);
  //check for non-existent letter
  search = letterFreq.find('x');
  REQUIRE(search==letterFreq.end());

}

TEST_CASE("Construction of tree","[tree construction]"){
  string sInputFile = "suhdude.txt";
  unordered_map<char,int> letterFreq = buildFreq(sInputFile);
  HuffmanTree *hTree = new HuffmanTree(letterFreq);
  std::shared_ptr<HuffmanNode> root = hTree->getRoot();
  //check tree height, size and root
  REQUIRE(root->getFrequency()==88);
  REQUIRE(hTree->getHeight()==7);
  REQUIRE(hTree->getSize()==55);


}

TEST_CASE("Construction of code table","[code table construction]"){
  string sInputFile = "suhdude.txt";
  unordered_map<char,int> letterFreq = buildFreq(sInputFile);
  HuffmanTree *hTree = new HuffmanTree(letterFreq);
  hTree->inOrder();
  //check number of fields and some letters with their frequencies
  int iFieldCount = 0;
  for (auto &it:hTree->getCodeTable()) {
        iFieldCount++;
    }
  REQUIRE(iFieldCount==28);
  auto search = hTree->getCodeTable().find('w');
  REQUIRE(search->second=="1110111");
  search = hTree->getCodeTable().find('r');
  REQUIRE(search->second=="01011");
  search = hTree->getCodeTable().find('?');
  REQUIRE(search->second=="01001");
  search = hTree->getCodeTable().find('T');
  REQUIRE(search->second=="010101");
}

TEST_CASE("Compressing of <InputFile>","[encoding]"){
  string sInputFile = "suhdude.txt";
  string sOutputFile = "ok";
  unordered_map<char,int> letterFreq = buildFreq(sInputFile);
  HuffmanTree *hTree = new HuffmanTree(letterFreq);
  hTree->inOrder();
  hTree->compressFile(sInputFile, sOutputFile);
  ifstream ifsOutput(sOutputFile);
  string line;
  getline(ifsOutput, line);
  REQUIRE(line.length()==391);
  REQUIRE(line.find("010001")==0);
  ifsOutput.close();

}

TEST_CASE("Compressing of <InputFile> to actual bit stream","[bit packing]"){
  string sInputFile = "suhdude.txt";
  string sOutputFile = "ok";
  unordered_map<char,int> letterFreq = buildFreq(sInputFile);
  HuffmanTree *hTree = new HuffmanTree(letterFreq);
  hTree->inOrder();
  hTree->compressFile(sInputFile, sOutputFile);
  //method bitpack is called within compressFile
  //ok.raw is generated
  //check file size
  string binaryFilename = sOutputFile+".raw";
  ifstream in(binaryFilename, ifstream::binary | ifstream::ate);
  int iFileSize = in.tellg();
  REQUIRE(iFileSize==53); //386/8+(386%8?1:0)+sizeof(int)
  in.close();
}

TEST_CASE("Unpacking bits to recreate original message","[bit unpacking]"){
  string sInputFile = "suhdude.txt";
  string sOutputFile = "ok";
  ifstream ifsInput(sInputFile);
  string sOriginal = "";
  if (!ifsInput){
      cout << "Opening " << sInputFile << " failed :(" << endl;
  } else {
      //read in char by char
      char cIn;
      while (ifsInput>>noskipws>>cIn){
        sOriginal += cIn;
      }
      ifsInput.close();
  }
  //check if original messaage is gotten
  unordered_map<char,int> letterFreq = buildFreq(sInputFile);
  HuffmanTree *hTree = new HuffmanTree(letterFreq);
  hTree->inOrder();
  hTree->compressFile(sInputFile, sOutputFile);
  string sDecode = hTree->bitunpack(sOutputFile+".raw");
  REQUIRE(sOriginal==sDecode);


}
