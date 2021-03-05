#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using integer = unsigned long long;

class RSA_Algorithm {
private:
	std::pair<integer, integer> publicKey;
	std::pair<integer, integer> privateKey;
public:
	RSA_Algorithm();
	integer encryption(int data);
	integer decryption(int data);
	void generateKey(int prime1, int prime2);
	integer greatestCommonDivisor(integer x, integer y);
};


