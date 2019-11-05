#include "arithmetic.h"

#include <iostream>
#include <cmath>

double Arithmetic::binary2Decimal(const bitset<32>& fraction)
{
	double dec = 0;
	for (int i = 0; i < 32; i++)
	{
		if (fraction[i] == 1)
		{
			dec += pow(2, -1 * (32 - i));
		}
	}
	return dec;
}

bitset<32> Arithmetic::decimal2Binary(double fraction)
{
	bitset<32> bin = 0;
	int i = 1;
	while (i <= 32 && fraction)
	{
		fraction *= 2;
		if (floor(fraction))
		{
			bin[32 - i] = 1;
			fraction -= 1;
		}
		i++;
	}
	return bin;
}

int Arithmetic::encode(const vector<unsigned char> & msg,
	int noOfSymbolsPerBlock,
	vector<bitset<32> > * encodedMsg)
{

	//calc prob
	for (auto& i : msg)
	{
		bool found = false;
		for (auto j : prob)
		{
			if (i == j.first)
			{
				found = true;
				j.second++;
				break;
			}
		}
		if (!found)
		{
			pair<unsigned char, int> p;
			p.first = i;
			p.second = 1;
		}
	}
	for (auto& i : prob)
	{
		i.second /= msg.size();
	}
	for (auto it = prob.begin() + 1; it != prob.end(); ++it)
	{
		it->second += (it - 1)->second;
	}


	int k = 0;
	int noOfBits = 0;
	while (k < msg.size())
	{
		double u = 1, l = 0, t = 0;
		for (int i = 0; i < noOfSymbolsPerBlock && k < msg.size(); i++)
		{
			for (auto j = prob.begin(); j != prob.end(); ++j)
			{

				if (j->first == msg[k])
				{
					if (j != prob.begin())
					{
						l += (j - 1)->second;
					}
					u = l + (u - l) * j->second;
					break;
				}
			}
			k++;
		}
		t = (u + l) / 2;
		noOfBits += 1 + log2(1 / (u - l));
		encodedMsg->push_back(decimal2Binary(t));
	}
	cout << "the number of bits: " << noOfBits << endl;
	cout << "the tags for everyblock: " << endl;
	for (auto i = encodedMsg->begin(); i != encodedMsg->end(); ++i)
	{
		cout << *i << endl;
	}
	return noOfBits;
}

void Arithmetic::decode(const vector<bitset<32> > & encodedMsg,
	int noOfSymbolsPerBlock,
	vector<unsigned char> * decodedMsg)
{
	int k = 0;
	while (k < encodedMsg.size())
	{
		double tag = binary2Decimal(encodedMsg[k]);
		double l = 0;
		double u = 1;
		for (int i = 0; i < noOfSymbolsPerBlock; i++)
		{
			tag = (tag - l)*100000 / (u*100000 - l*100000);
			for (auto j=prob.begin(); j!=prob.end();++j)
			{
				if (j == prob.begin())
				{
					if (tag < j->second)
					{
						u = j->second;
						decodedMsg->push_back(j->first);
					}
				}
				else if (tag < j->second && tag > (j - 1)->second)
				{
					u = j->second;
					l = (j - 1)->second;
					decodedMsg->push_back(j->first);
					break;
				}
			}
		}
		k++;
	}
}
