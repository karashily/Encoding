#include "headers/arithmetic.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	string mode = argv[1];
	Arithmetic a;
	ofstream fout;

	if (mode == "-bin_to_dec") {
		cout << "The Decimal value is: " << a.binary2Decimal(atoi(argv[2])) << endl;
	}

	if (mode == "-dec_to_bin") {
		cout << "The Binary Value is: " << a.decimal2Binary(stod(argv[2])) << endl;
	}

	vector<unsigned char> input;
	vector<bitset<32>> encodedMsg;

	if (mode == "-encode") {
		string format;
		cin >> format;
		int xRes, yRes;
		cin >> xRes >> yRes;
		int maxIntensity;
		cin >> maxIntensity;
		for (int i = 0; i < xRes * yRes; i++) {
			int x;
			cin >> x;
			input.push_back(x);
		}
		int noOfBits = a.encode(input, atoi(argv[2]), &encodedMsg);
		cout << "Compression Ratio: " << (8.0 * xRes * yRes) / noOfBits 
			<< endl;
		cout << "Number of bits: " << noOfBits << endl;

		//  write the encoded image & its parameters
		fout.open("encoded_image.enc");
		fout << noOfBits << endl;
		fout << encodedMsg.size() << endl;

		for (int i = 0; i< int(encodedMsg.size()); i++) {
			fout << encodedMsg[i] << endl;
		}
		fout.close();
	}

	if (mode == "-decode") {
		int noOfBits;
		cin >> noOfBits;
		
		int msgSize;
		cin >> msgSize;
		encodedMsg.resize(msgSize);
		
		for (int i = 0; i < msgSize; i++) {
			cin >> encodedMsg[i];
		}

		vector<unsigned char> decodedMsg;
		a.decode(encodedMsg, atoi(argv[2]), &decodedMsg);

		// write the decoded image
		fout.open("decoded_image.pgm");
		fout << "P2" << endl;
		fout << atoi(argv[3]) << " " << atoi(argv[4]) << endl;
		fout << atoi(argv[5]) << endl;
		int k = 0;
		for (int i = 0; i < atoi(argv[3]); i++) {
			for (int j = 0; j < atoi(argv[4]); j++) {
				fout << int(decodedMsg[k]++) << " ";
			}
			fout << endl;
		}
	}

	return 0;
}