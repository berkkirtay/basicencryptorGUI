#include "RSA_Algorithm.h"
#include "BASICXOR_Algorithm.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>


class FILEO {
private:
	std::vector<std::string> textLines;
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
	char* buffer8_t = nullptr;
	int filesize = 0;

public:
	FILEO(std::string fileName, std::string outFileName, int opt);
	~FILEO() { delete[] buffer8_t; }
	void createKey(RSA_::integer key);
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



