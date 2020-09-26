#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <vector>


#pragma once

class RSA_Algorithm{
private:
	std::pair<int, int> publicKey;
	std::pair<int, int> privateKey;
public:
	RSA_Algorithm();
	int encryption(int data);
	int decryption(int data);
	void generateKey(int prime1, int prime2);
	int greatestCommonDivisor(int x, int y);
};
