#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
class ModEllipticCurve{
public:
	ModEllipticCurve();
	ModEllipticCurve(__int64 Coefficients[5],__int64 prime);
	ModEllipticCurve( const __int64 Coefficients[5], const __int64 &prime);
	void set(__int64 Coefficients[5], __int64 prime);
	int PointEvaluation(std::pair<__int64, __int64> Point);
	std::pair<__int64, __int64> FindPoint();
	int xSearch(__int64 xCoord);
	int GetGradient(std::pair<__int64, __int64> Point);
	std::pair<__int64, __int64> DoublePoint(std::pair<__int64, __int64> Point);
	std::pair<__int64, __int64> AddedPoint(std::pair<__int64, __int64> Point1, std::pair<__int64, __int64> Point2);
	std::pair<__int64, __int64> MultipliedPoint(std::pair<__int64, __int64> Point, __int64 mult);
	void printPoint(std::pair <__int64, __int64> Point);
	int GetOrder(std::pair <__int64, __int64> Point);
	
	//std::pair< std::pair<__int64, __int64>, std::pair<__int64, __int64>> GetCipherText(std::pair<__int64, __int64>, std::pair<__int64, __int64>);
	std::pair<__int64, __int64> Decrypt(std::pair<__int64, __int64>, std::pair<__int64, __int64>, int privateKey);
	//std::pair<__int64, __int64> characterTransformation(std::pair<__int64, __int64>, char);
	//void encryptMessage(std::pair<__int64, __int64>, std::string);
	
	//std::string decryptMessage(std::pair<__int64, __int64>, std::string);
	//std::map<std::pair<__int64, __int64>, char> createDictionary(std::pair<__int64, __int64>);

private:
	__int64 Coefficients[5];
	__int64 prime;
	std::pair <__int64, __int64> infinity;

};

