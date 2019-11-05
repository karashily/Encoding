#include <iostream>
#include <fstream>
#include <string>

#include "headers/huffman.hpp"

int main(int argc, char* argv[]) {
	string mode = argv[1];
	Huffman h;
	ofstream fout;

	vector<Symbol> prob;

	if (mode == "-entropy") {
		string format;
		cin >> format;

		int xRes, yRes;
		cin >> xRes >> yRes;

		int maxIntensity;
		cin >> maxIntensity;

		vector<unsigned char> input;
		for (int i = 0; i < xRes * yRes; i++) {
			int x;
			cin >> x;
			input.push_back(x);
		}

		cout << "Entropy = " << h.computeEntropy(input, &prob) << endl;
		
	}

	if (mode == "-tree") {
		string format;
		cin >> format;

		int xRes, yRes;
		cin >> xRes >> yRes;

		int maxIntensity;
		cin >> maxIntensity;

		vector<unsigned char> input;
		for (int i = 0; i < xRes * yRes; i++) {
			int x;
			cin >> x;
			input.push_back(x);
		}
		h.computeEntropy(input, &prob);
		h.buildTree(prob);
		h.printCodeTable();
	}

	vector<unsigned int> encodedMsg;

	if (mode == "-encode") {
		string format;
		int xRes, yRes;
		int maxIntensity;
		vector<unsigned char> input;

		cin >> format;
		cin >> xRes >> yRes;
		cin >> maxIntensity;

		if (argc == 2) {
			// normal encoding
			for (int i = 0; i < xRes * yRes; i++) {
				int x;
				cin >> x;
				input.push_back(x);
			}
		} else {
			// correlation encoding
			int lastX = 0;
			for (int i = 0; i < xRes * yRes; i++) {
				int x;
				cin >> x;
				input.push_back(x-lastX);
				lastX = x;
			}
		}

		h.computeEntropy(input, &prob);
		h.buildTree(prob);
		int noOfBits = h.encode(input, &encodedMsg);

		cout << "Compression Ratio: " << (8.0 * xRes * yRes) / noOfBits
			 << endl;
		cout << "The Number of Bytes = " << ceil(noOfBits/8.0) << endl;

		//  write the encoded image & its parameters
		fout.open("encoded_image.enc");
		fout << noOfBits << endl;
		fout << encodedMsg.size() << endl;

		for (int i = 0; i< int(encodedMsg.size()); i++) {
			fout << encodedMsg[i] << endl;
		}
		fout.close();
	}

	return 0;
}