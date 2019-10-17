# Makefile for Assignemnt 3
# 10 Apr 2018
# Tony Guo
# GXXHEN001

huffencode: main.o
	g++ -o huffencode main.o HuffmanTree.o HuffmanNode.o -std=c++11

main.o: main.cpp HuffmanTree.o
	g++ -c -o main.o main.cpp -std=c++11

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h HuffmanNode.o
	g++ -c -o HuffmanTree.o HuffmanTree.cpp -std=c++11

HuffmanNode.o: HuffmanNode.cpp HuffmanNode.h
	g++ -c -o HuffmanNode.o HuffmanNode.cpp -std=c++11

run:
	./huffencode suhdude.txt ok
	./huffencode wassupaguy.txt wassup

test:
	g++ -c -o tests-main.o tests-main.cpp -std=c++11
	g++ -o tests tests-main.o tests-huffmantree.cpp HuffmanTree.o HuffmanNode.o -std=c++11

runtest:
	./tests

clean:
	@rm -f *.o huffencode *.raw *.hdr ok wassup tests
