#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Define a symbol struct here to hold the symbol (grayscale value)
// and its probability/frequency
struct Symbol {
	// Grayscale value of the symbol
	unsigned char val;
	// Probability of that symbol
	double prob;
};

// Define the tree node struct here ...
struct Node {
	// the right child of the node
	Node* right;
	// the left child of the node
	Node* left;
	// the symbol of the node
	Symbol s;
	// the total probabilty of node children
	double totProb;

	bool operator ()(Node* x, Node* y)
	{
		return (x->totProb > y->totProb);
	}
};


class Huffman {
public:
	// Constructor and destructor
	Huffman() { }

	// A function to compute the entropy of the input message and
	// stores the probabilities of the different symbols in
	// the input array.
	float computeEntropy(const vector<unsigned char>& msg,
		vector<Symbol>* prob);

	// A function to build the Huffman tree given the computed
	// symbol probabilities.
	void buildTree(const vector<Symbol>& prob);

	// A function to print the code table computed from the build_tree above.
	void printCodeTable();

	// A function to encode the input message using the computed tree 
	// and store the output in the output array, where each entry
	// corresponds to the codeword for an input symbol in the message.
	//
	// The function should return the number of bits in the encoded 
	// message.
	int encode(const vector<unsigned char>& msg,
		vector<unsigned int>* encodedMsg);

private:
	// Data members here ... for example to store the tree and the codeword 
	// hash table
	Node* tree;
	// ..
	vector<pair<unsigned char, unsigned long long>> hashTable;
	void getHashCode(Node* node, int hashCode, int lvl);
};

#endif