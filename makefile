all:
	Arithmetic Huffman

Arithmetic:
	g++ arithmetic.cpp headers/arithmetic.cpp -o arithmetic.exe

Huffman:
	g++ huffman.cpp headers/huffman.cpp -o huffman.exe