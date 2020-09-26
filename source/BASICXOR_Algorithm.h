#pragma once
class BASICXOR_Algorithm
{
private:
	int key=0;

public:
	BASICXOR_Algorithm();
	void generateKey(int prime1, int prime2);
	int encryption(int data);
	int decryption(int data);
};

