
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "ECDHDecryptor.h"

using namespace std;

int main()
{

	cout << "Enter the address of the private key: " << flush;


	string privateKeyAddress;
	getline(cin, privateKeyAddress);

	ifstream documents;
	documents.open(privateKeyAddress);
	
	__int64 a0;
	documents >> a0;

	__int64 a1;
	documents >> a1;

	__int64 a2;
	documents >> a2;

	__int64 a3;
	documents >> a3;

	__int64 a4;
	documents >> a4;


	__int64 prime;
	documents >> prime;

	__int64 Coefficients[5] = { a0, a1, a2, a3, a4 };

	__int64 startingxCoord;
	documents >> startingxCoord;

	__int64 startingyCoord;
	documents >> startingyCoord;

	__int64 xCoord;
	documents >> xCoord;


	__int64 yCoord;
	documents >> yCoord;

	__int64 privateKey;
	documents >> privateKey;

	documents.close();
	documents.clear();

	string dictionaryAddress;
	cout << "Enter the address of the dictionary: " << flush;
	getline(cin, dictionaryAddress);

	documents.open(dictionaryAddress);
	map<pair<__int64, __int64>, char> dict;
	while (!documents.eof()) {
		char letter;
		documents >> letter;
		__int64 xCoord;
		documents >> xCoord;
		__int64 yCoord;
		documents >> yCoord;
		pair<__int64, __int64> p(xCoord,yCoord);
		dict[p] = letter;
	}

	documents.close();
	documents.clear();
	







	string encryptedMessageAddress;
	cout << "Enter the address of the encrypted message: " << flush;
	getline(cin, encryptedMessageAddress);

	ECDHDecryptor Decryptor(Coefficients, prime);

	string s = Decryptor.decryptMessage(dict, encryptedMessageAddress,privateKey);
	s.pop_back();
	cout << s << endl;

	documents.close();
	documents.clear();

	return 0;
}


