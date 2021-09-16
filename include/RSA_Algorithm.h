#include <iostream>
#include <string>
#include <math.h>
#include <vector>

namespace RSA_ {
	using integer = unsigned long long;

	class RSA_Algorithm {
	private:
		std::pair<integer, integer> publicKey;
		std::pair<integer, integer> privateKey;
		integer basicXOR(integer data, int opt);
		integer greatestCommonDivisor(integer x, integer y);
	public:
		RSA_Algorithm();
		integer encryption(integer data);
		integer decryption(integer data);
		void generateKey(int prime1, int prime2);
	};
}
