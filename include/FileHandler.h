#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>
#include "Encryptor.cpp"

class FileHandler {
private:
	const int ENCRYPTION = 0;
	const int DECRYPTION = -1;

private:
	std::unique_ptr<Encryptor> encryptor = nullptr;
	std::vector<std::string> textLines;
	std::vector<long> decryptedDATA;
	std::vector<long> encryptedDATA;
	std::string fileName;
	std::string outFileName;
	std::fstream FILE;
	char* buffer8_t = nullptr;
	size_t filesize = 0;

private:
	void readOriginalFile();
	void writeFile(int opt);
	void readEncryptedFile();
	void setOutputFileName();

public:
	FileHandler(std::string fileName, std::string outFileName);
	~FileHandler();
	void readAndEncrypt();
	void readAndDecrypt();
	void initializeEncryptor(int prime1, int prime2);
};

