/*
MIT License

Copyright (c) 2020 Berk Kirtay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "FileHandler.h"
using namespace RSA_;

FileHandler::FileHandler(std::string fileName, std::string outFileName) {
    this->fileName = fileName;
    this->outFileName = outFileName;   
}

void FileHandler::initializeEncryptor(int prime1, int prime2) {
    encryptor = std::make_unique<Encryptor>(Encryptor(prime1, prime2));
}

FileHandler::~FileHandler(){
    delete[] buffer8_t;
}

void FileHandler::readAndEncrypt() {
    readOriginalFile();
    encryptedDATA = encryptor->encryptFile(buffer8_t, filesize);
    writeFile(ENCRYPTION);
}

void FileHandler::readAndDecrypt() {
    readEncryptedFile();
    decryptedDATA = encryptor->decryptFile(textLines);
    writeFile(DECRYPTION);
}

void FileHandler::readOriginalFile() {
    std::fstream FILE;
    try {
        FILE.open(fileName, std::ios::in | std::ios::binary | std::ios::ate);
        if (!FILE) {
            throw "File can't be opened!";
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        system("pause");
    }
    if (FILE) {
        std::streampos size = FILE.tellg();
        buffer8_t = new char[size];
        FILE.seekg(0, std::ios::beg);
        filesize = size;
        FILE.read(buffer8_t, size);
        FILE.close();
    }
}

void FileHandler::readEncryptedFile() {
    std::fstream FILE;
    try {
        FILE.open(fileName, std::ios::in | std::ios::binary);
        if (!FILE)
            throw "File can't be opened!";
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        system("pause");
    }
    while (FILE) {
        std::string newLine;
        getline(FILE, newLine);
        textLines.push_back(newLine);
    }
    FILE.close();
}

void FileHandler::writeFile(int opt) {
    setOutputFileName();

    std::fstream OUTFILE;
    try {
        OUTFILE.open(outFileName, std::ios::out | std::ios::binary);
        if (!OUTFILE)
            throw "File can't be opened!";
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        system("exit");
    }

    if (opt == DECRYPTION) {
        for (std::vector<long>::iterator it = decryptedDATA.begin(); it != decryptedDATA.end(); it++) {
            while (*it != 0) {
                OUTFILE << static_cast<char>(*it & 0x00000000000000FF);
                *it >>= 8;
            }
        }
    }
    else {
        for (std::vector<long>::iterator it = encryptedDATA.begin(); it != encryptedDATA.end(); it++) {
            OUTFILE << std::hex << *it << std::endl;
        }
    }
    OUTFILE.close();
}

/*
 * We set name of the output file to get the same extension.
 * For example: DecryptedFILE -> DecryptedFILE.txt
 */
void FileHandler::setOutputFileName() {
    std::string tempName = fileName;
    for (int a = 0; a < tempName.length(); a++) {  
        if (tempName[a] == '.') {
            for (int j = a; j < tempName.length(); j++) {
                outFileName.push_back(tempName[j]);
            }
            break;
        }
    }
}
