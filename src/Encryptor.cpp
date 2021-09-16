#include <thread>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "RSA_Algorithm.h"

using namespace RSA_;

class Encryptor {
private:
    std::unique_ptr<RSA_Algorithm> newEncryption = nullptr;
    std::vector<std::string> textLines;
    std::unordered_map<std::string, int> textHashMap;
    std::unordered_map<std::string, long> textCaches;
    std::vector<long> decryptedDATA;
    std::vector<long> encryptedDATA;
    size_t filesize = 0;

private:
    /*
    * We use a hashmap for the same encrypted data
    * to get more efficiency for decryption process.
    * Simply, for the same data, it does not ignite decryption,
    * it just puts the decrypted data from the hashmap. 
    */

    void decryptionThread(std::vector<long>& decArr, int first_boundary, int second_boundary) {
        for (int x = first_boundary; x < second_boundary; x++) {
            if (textLines.at(x) == "") {
                break;
            }
            if (textHashMap[textLines[x]] > 1 && textHashMap[textLines[x]] < 900) {
                textHashMap[textLines[x]] = 9999;
                long data = Decrypt(std::stoul(textLines[x], nullptr, 16));
                textCaches[textLines[x]] = data;
                decArr.push_back(data);
            }
            else if (textHashMap[textLines[x]] == 1) {
                long data = Decrypt(std::stoul(textLines[x], nullptr, 16));
                textCaches[textLines[x]] = data;
                decArr.push_back(data);
            }
            else {
                decArr.push_back(textCaches[textLines[x]]);
            }
        }
    }

    integer Encrypt(std::vector<char> subStr) {
        integer encodedString = 0;
        for (int i = 0; i < subStr.size(); i++) {
            if (i != 0) encodedString <<= 8;
            char code = subStr[i];
            encodedString |= code;
        }
        return newEncryption->encryption(encodedString);
    }

    integer Decrypt(integer encryptedStr) {
        return newEncryption->decryption(encryptedStr);
    }

public:
	Encryptor(int prime1, int prime2) {
        newEncryption = std::make_unique<RSA_Algorithm>(RSA_Algorithm());
        newEncryption->generateKey(prime1, prime2);
	}

    std::vector<long> encryptFile(char* buffer8_t, size_t filesize) {
        int x = 0;  

       for (; x < filesize - 2; x += 3) {
            std::vector<char> cryptoBlock = { buffer8_t[x + 2], buffer8_t[x + 1], buffer8_t[x] };
            integer data = Encrypt(cryptoBlock);
            encryptedDATA.push_back(data);
        } 
        

        for (; x < filesize - 1; x += 2) {
            std::vector<char> cryptoBlock = { buffer8_t[x + 1], buffer8_t[x] };
            integer data = Encrypt(cryptoBlock);
            encryptedDATA.push_back(data);
        }

        for (; x < filesize; x++) {
            std::vector<char> cryptoBlock = { buffer8_t[x] };
            integer data = Encrypt(cryptoBlock);
            encryptedDATA.push_back(data);
        }

        return encryptedDATA;
    }

    std::vector<long> decryptFile(std::vector<std::string> textLines) {
        for (int i = 0; i < textLines.size(); i++) {
            textHashMap[textLines[i]]++;
        }

        this->textLines = textLines;
        std::vector<long> dec1;
        std::vector<long> dec2;
        std::vector<long> dec3;
        std::vector<long> dec4;

        std::thread thrd1([&] {decryptionThread(dec1, 0, textLines.size()); });
     //   std::thread thrd2([&] {decryptionThread(dec2, textLines.size() / 4, textLines.size() / 2); });
     //   std::thread thrd3([&] {decryptionThread(dec3, textLines.size() / 2, (textLines.size() * 3) / 4); });
     //   std::thread thrd4([&] {decryptionThread(dec4, (textLines.size() * 3) / 4, textLines.size()); });

        thrd1.join();
       // thrd2.join();
       // thrd3.join();
       // thrd4.join();

        for (int i = 0; i < dec1.size(); i++) {
            decryptedDATA.push_back(dec1[i]);
        }
        for (int i = 0; i < dec2.size(); i++) {
            decryptedDATA.push_back(dec2[i]);
        }
        for (int i = 0; i < dec3.size(); i++) {
            decryptedDATA.push_back(dec3[i]);
        }
        for (int i = 0; i < dec4.size(); i++) {
            decryptedDATA.push_back(dec4[i]);
        }
        return decryptedDATA;    
    }
};
