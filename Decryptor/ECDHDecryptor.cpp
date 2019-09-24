#include "ECDHDecryptor.h"
#include <string>

using namespace std;

ECDHDecryptor::ECDHDecryptor(__int64 Coefficients[5], __int64 prime) {
	ModEllipticCurve F(Coefficients, prime);
	E = F;
}

std::pair<__int64, __int64> ECDHDecryptor::Decrypt(std::pair<__int64, __int64> B1, std::pair<__int64, __int64> B2, __int64 privateKey) {
	std::pair<__int64, __int64> multB1 = E.MultipliedPoint(B1, -privateKey);
	std::pair<__int64, __int64> M = E.AddedPoint(B2, multB1);
	return M;
}

string ECDHDecryptor::decryptMessage(map<pair<__int64, __int64>, char> dict, string encryptedMessagelog, __int64 privateKey) {

	ifstream EncryptedFile;
	EncryptedFile.open(encryptedMessagelog);
	
	string s;
	while (!EncryptedFile.eof()) {

		string line;
		__int64 B1xCoord;
		__int64 B1yCoord;
		__int64 B2xCoord;
		__int64 B2yCoord;
		EncryptedFile >> B1xCoord;
		getline(EncryptedFile, line, ' ');
		EncryptedFile >> B1yCoord;
		getline(EncryptedFile, line, ' ');
		EncryptedFile >> B2xCoord;
		getline(EncryptedFile, line, ' ');
		EncryptedFile >> B2yCoord;

		
		
		std::pair<__int64, __int64> B1(B1xCoord, B1yCoord);
		std::pair<__int64, __int64> B2(B2xCoord, B2yCoord);
		std::pair<__int64, __int64> point = Decrypt(B1, B2, privateKey);
		char e = dict[point];
		
		s += e;





	}

	return s;
}