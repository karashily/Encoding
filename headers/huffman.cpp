#include "huffman.hpp"

// Your implementations here

#include <queue>
using namespace std;


float Huffman::computeEntropy(const vector<unsigned char>& msg,
	vector<Symbol>* prob)
{
	double entropy;
	for (auto& i : msg)
	{
		bool found = false;
		for (auto j = prob->begin(); j != prob->end(); j++)
		{
			if (i == j->val)
			{
				found = true;
				j->prob++;
				break;
			}
		}
		if (!found)
		{
			Symbol symbol;
			symbol.prob = 1;
			symbol.val = i;
			prob->push_back(symbol);
		}
	}
	for (auto i = prob->begin(); i != prob->end(); i++)
	{
		i->prob /= msg.size();
		entropy -= (i->prob) * log2(i->prob);
	}
	return entropy;
}

void Huffman::buildTree(const vector<Symbol>& prob)
{
	priority_queue<Node*, vector<Node*>, Node> minHeap;
	for (auto& i : prob)
	{
		Node* node = new Node;
		node->left = NULL;
		node->right = NULL;
		node->s = i;
		node->totProb = i.prob;
		minHeap.push(node);
	}
	while (!minHeap.empty())
	{
		Node* right = new Node;
		right = minHeap.top();
		minHeap.pop();
		if (minHeap.empty())
		{
			tree = right;
		}
		else
		{
			Node* left = new Node;
			left = minHeap.top();
			minHeap.pop();

			Node* parent = new Node;
			parent->left = left;
			parent->right = right;
			parent->s.prob = -1;
			parent->s.val = -1;
			parent->totProb = left->totProb + right->totProb;
			tree = parent;
			minHeap.push(parent);
		}
	}
	getHashCode(tree, 0, 0);
}

void Huffman::getHashCode(Node* node, int hashCode, int lvl)
{
	if (node->left == NULL && node->right == NULL)
	{
		pair<unsigned char, int> p;
		p.first = node->s.val;
		p.second = hashCode;
		hashTable.push_back(p);
		return;
	}
	getHashCode(node->right, hashCode, lvl + 1);
	getHashCode(node->left, hashCode + pow(2, lvl), lvl + 1);
}

void Huffman::printCodeTable()
{
	for (auto& i : hashTable)
	{
		cout << int(i.first) << " " << i.second << endl;
	}
}

int Huffman::encode(const vector<unsigned char> & msg,
	vector<unsigned int> * encodedMsg)
{
	int noOfBits = 0;
	for (auto& i : msg)
	{
		for (auto j : hashTable)
		{
			if (i == j.first)
			{
				encodedMsg->push_back(j.second);
				if (j.second) noOfBits += floor(log2(j.second) + 1);
				break;
			}
		}
	}
	return noOfBits;
}

