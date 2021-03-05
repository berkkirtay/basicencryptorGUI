#include "BASICXOR_Algorithm.h"
BASICXOR_Algorithm::BASICXOR_Algorithm() {}

void BASICXOR_Algorithm::generateKey(int prime1, int prime2) {
	int Q = (prime1 * prime2) % (prime1 + prime2);
	int Qn =(prime1 - 1)* (prime2 - 1);
	while (prime1 > 2) {
		prime2 += prime1 % 7;
		prime1 /= 7;
	}
	key = (Qn * Q) + (Qn*prime2);
}

int BASICXOR_Algorithm::encryption(int data) {
	data -= key / 10;
	data ^= key; // it's very simple
	return data;
}

int BASICXOR_Algorithm::decryption(int data) {
	data ^= key;
	data += key / 10;
	return data;
}