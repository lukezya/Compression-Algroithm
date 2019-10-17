# README for Assignment 3
# 10 Apr 2018
# Tony Guo
# GXXHEN001

-----------------------------------
Files in this directory
-----------------------------------
HuffmanNode.cpp - source file containing the body of method signatures in
HuffmanNode.h for node of binary tree(HuffmanTree).

HuffmanNode.h - method headers for source file HuffmanNode.cpp.

HuffmanTree.cpp - source file containing the body of method signatures in
HuffmanTree.h for building tree, managing tree and compressing data.

HuffmanTree.h - method headers for source file HuffmanTree.cpp.

main.cpp - driver source file for compressing an input file to an output file
and contains the main() method.

Makefile - makefile to compile source files and get: huffencode, main.o,
HuffmanTree.o, and HuffmanNode.o.

suhdude.txt - test data file for compressing with created executable huffencode.

wassupaguy.txt - test data file for compressing with created executable
huffencode.

tests-main.cpp - main unit test file that define CATCH_CONFIG_MAIN for the rest
of the test files.

tests-huffmantree.cpp - unit test for HuffmanTree containing tests for all
methods: frequency counting, tree construction, code table construction,
encoding, bit packing, and bit unpacking.

-----------------------------------
Running huffencode
-----------------------------------
Open this directory in terminal.

Run the following commands:
make clean
make
make run

*make run will run the executable huffencode 2 times:
1) ./huffencode suhdude.txt ok
2) ./huffencode wassupaguy.txt wassup
-> with 2 different input files to 2 different output files
---The above values for the operation arguments were used for demo runs---

The following files will be created:
1) -> ok            - compressed file containing string buffer
   -> ok.hdr        - header file containing no. of fields and
                      fields with letter and its string code
   -> ok.raw        - actual compressed binary file
2) -> wassup        - compressed file containing string buffer
   -> wassup.hdr    - header file containing no. of fields and
                      fields with letter and its string code
   -> wassup.raw    - actual compressed binary file

-----------------------------------
Running unit tests
-----------------------------------
Open this directory in terminal.

After running the commands above in "Running huffencode",
Run the following commands:
make test
make runtest

The file "tests" will be created, and make runtest runs this executable.
The results of the unit tests will be outputted to console.

-----------------------------------
Running huffencode with own arguments
-----------------------------------
Open terminal in this directory.
Create an English textfile and save it in the same directory.

To run huffencode with own arguments, type in a command in the following form:
./huffencode <input_file> <output_file>

To run this command with available test data, run any of the following commands:
./huffencode suhdude.txt ok
./huffencode wassupaguy.txt wassup

The following output files will be created:
<output_file>     - compressed file containing string buffer
<output_file>.hdr - header file containing no. of fields and
                    fields with letter and its string code
<output_file>.raw - actual compressed binary file
