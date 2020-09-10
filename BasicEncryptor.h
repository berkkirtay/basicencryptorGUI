
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>


class FILEO {
private:
	std::vector<std::string> textLines; // using vector instead of array is far more efficient for memory handling!
	std::string fileName;
	std::string outFileName;
	std::fstream FILE;
	int x=0;
	int y=0;
	int progress = 0;
	

public:
	FILEO(std::string fileName, std::string outFileName, int opt);
	~FILEO();
public:
	void createKey(int key);
	int getX();
	int getY();
	void readingFile();
	void writingFile();
	void lineEncrypt(std::string& line, int prime1, int prime2, int option, int row);
	void encrypt(int prime1, int prime2, int option);
	int getProgress();
};

//Global prototypes
int greatestCommonDivisor(int x, int y);
int isPrime(int prime);
bool isValidChar(char CHAR);



