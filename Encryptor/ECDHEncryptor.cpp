#include "ECDHEncryptor.h"
#include <time.h>


ECDHEncryptor::ECDHEncryptor(__int64 Coefficients[5], __int64 prime) {
	ModEllipticCurve F(Coefficients, prime);
	E = F;
}

std::pair<__int64, __int64> ECDHEncryptor::characterTransformation(std::pair<__int64, __int64> startingPoint, char letter) {
	__int64 v = int(letter);
	std::pair<__int64, __int64> point = E.MultipliedPoint(startingPoint, v);
	return point;
}

vector<pair<__int64, __int64>> ECDHEncryptor::messageTransformation(std::pair<__int64, __int64> startingPoint, std::string message) {
	vector<pair<__int64, __int64>> v;
	for (string::iterator it = message.begin(); it != message.end(); it++) {
		std::pair<__int64, __int64> pointFromLetter = E.characterTransformation(startingPoint, *it);
		//cout << pointFromLetter.first << " " << pointFromLetter.second << endl;
		v.push_back(pointFromLetter);
	}
	return v;
}

std::pair< std::pair<__int64, __int64>, std::pair<__int64, __int64>> ECDHEncryptor::GetCipherText(std::pair<__int64, __int64> M, std::pair<__int64, __int64> PublicKey, std::pair<__int64, __int64> startingPoint) {
	
	int k = rand();
	
	
	std::pair<__int64, __int64> B1 = E.MultipliedPoint(startingPoint, k);
	std::pair<__int64, __int64> multPublicKey = E.MultipliedPoint(PublicKey, k);
	std::pair<__int64, __int64> B2 = E.AddedPoint(M, multPublicKey);

	return std::pair<std::pair<__int64, __int64>, std::pair<__int64, __int64>>(B1, B2);
}

void ECDHEncryptor::encrypt(vector<pair<__int64, __int64>> transormedMessage, std::pair<__int64, __int64> publicKey, std::pair<__int64, __int64> startingPoint) {
	srand(time(0));
	ofstream encryptedMessage;
	encryptedMessage.open("encryptedMessage.txt");
	for (int i = 0; i < transormedMessage.size(); i++) {
		pair<__int64, __int64> point = transormedMessage[i];
		std::pair< std::pair<__int64, __int64>, std::pair<__int64, __int64>> encryptedPoint = GetCipherText(point, publicKey, startingPoint);
		encryptedMessage << encryptedPoint.first.first << " " << encryptedPoint.first.second << " " << encryptedPoint.second.first << " " << encryptedPoint.second.second << endl;
	}
}