#include "RSA_Algorithm.h"
#include "BASICXOR_Algorithm.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>


class FILEO {
private:
	std::vector<std::string> textLines; // using vector instead of array is far more efficient for memory handling!
	std::vector<int> decryptedDATA;
	std::vector<int> encryptedDATA;
	std::string fileName;
	std::string outFileName;
	std::fstream FILE;
	int x=0;
	int y=0;
	int progress = 0;
	int option;
	int encryptionType = 0;

public:
	FILEO(std::string fileName, std::string outFileName, int opt);
	void createKey(int key);
	int getX();
	int getY();
	void readingFile(int opt);
	void writingFile(int opt);
	void encrypt(int prime1, int prime2, int option);
	void setopt(int opt);
	void setencry(int opt);
	int getProgress();
};

//Global prototypes
int isPrime(int prime);
//bool isValidChar(char CHAR);



