#include "BasicEncryptor.h"
/*MIT License

Copyright (c) 2020 trantor00

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

/*
   THIS PROGRAM IS ONLY FOR EDUCATIONAL OR TRAINING. It shouldn't be used for professional purposes.
This time I used exact RSA Algorithm to strengthen encryption.
   Program's handling every character separately(It processes new character every turn),
   So, it works a bit slowly if we try handling big files like mp4, zip, iso etc. Of course It's way too more suitable using with text files.
   Built by trantorberk
*/

using namespace std; // standart library namespace
using namespace RSA_;

//definitions
FILEO::FILEO(string fileName, string outFileName, int opt) {
    this->fileName = fileName;
    this->outFileName = outFileName;   
}


void FILEO::createKey(RSA_::integer key) { 
    // In order to get bigger primes we should do some changes here.
    // We can directly assign prime numbers explicitly if the prime numbers are too big to generate.
    x += key % 2111; key /= 13;
    x += key % 3333;
    key *= x;
    y += (key % x);
    while (true) {  //creating 2 prime numbers from the key given.  
        y += key % 3;
        if (isPrime(x) && x>3000) {
            y += key % x;
            while (true) {
                if (isPrime(y) && y != x && y > x+2000) {
                    break;
                }
                else {
                    y++;
                }
            }
            break;
        }
        else x++;
    }  
}
int FILEO::getX() {
    return x;
}
int FILEO::getY() {
    return y;
}

void FILEO::readingFile(int opt) {
    fstream FILE;
    if(opt !=-1){
    try {
    FILE.open(fileName, ios::in | std::ios::binary | std::ios::ate);
    if (!FILE) {
        throw "File can't be opening!";
    }
    }
    catch (exception& e) {
         cout << "FILE HANDLING ERROR: " << e.what() << endl;
         system("pause");
    }
    if (FILE) {
        std::streampos size = FILE.tellg();
        buffer8_t = new char[size];
        FILE.seekg(0, std::ios::beg);
        filesize = size;
        FILE.read(buffer8_t, size);
        progress += size / 5;
        FILE.close();
    }
    }
    else {
        try {
            FILE.open(fileName, ios::in | std::ios::binary);
            if (!FILE)
                throw "File can't be opening!";
        }
        catch (exception& e) {
            cout << "FILE HANDLING ERROR: " << e.what() << endl;
            system("pause");
        }
            while(FILE) {                    
                string newLine;
                getline(FILE, newLine);
                textLines.push_back(newLine);
                progress++;
            }
            FILE.close();
        }     
    }

void FILEO::writingFile(int opt) {
    fstream OUTFILE;
    try {
        OUTFILE.open(outFileName, ios::out | ios::binary);
        if (!OUTFILE)
            throw "File can't be opening!";
    }
    catch (exception& e) {
        cout << "FILE HANDLING ERROR: " << e.what() << endl;
        system("pause");
    }
    if (opt == -1) {
        for (vector<int>::iterator it = decryptedDATA.begin(); it != decryptedDATA.end(); it++) {
           OUTFILE << static_cast<char>(*it); 
        }
    }
    else {
      //  OUTFILE << fileName << endl;  // for remembering the file name later..
        for (vector<int>::iterator it = encryptedDATA.begin(); it != encryptedDATA.end(); it++) {
            OUTFILE << static_cast<int>(*it) << endl;
        }
    }
    OUTFILE.close();
}

void FILEO::encrypt(int prime1, int prime2, int option) {
    string tempName = fileName;
    for (int a = 0; a < tempName.length(); a++) {  // for the same file extension output..
        if (tempName[a] == '.') {
            for (int j = a; j < tempName.length(); j++) {
                outFileName.push_back(tempName[j]);
            }
            break;
        }
    }
    if (encryptionType == 0) {
        RSA_Algorithm newEncryption;  // RSA_Algorithm class
        newEncryption.generateKey(prime1, prime2);
            if (option == -1) {  //decryption
            /*    for (vector<string>::iterator it = textLines.begin(); it != textLines.end(); it++) {
                    if (*it == "") { break; }
                 /*   if (it == textLines.begin()) {
                        outFileName = *it + ".DEC";
                        continue;
                    }
                    int data = newEncryption.decryption(stoi(*it));
                    decryptedDATA.push_back(data);
                    progress++;
                }*/

                // I just pre-implemented those threads.. It's experimental but can be improved later.
                std::vector<int> dec1;
                std::thread thrd1([&] {
                    for (int x = 0; x < textLines.size() / 2; x++) {
                        if (textLines.at(x) == "") {
                            break;
                        }
                        int data = newEncryption.decryption(stoi(textLines.at(x)));
                        dec1.push_back(data);
                        progress++;
                    }
                });
                std::vector<int> dec2;
                std::thread thrd2([&] {
                    for (int x = textLines.size() / 2; x < textLines.size(); x++) {
                        if (textLines.at(x) == "") {
                            break;
                        }
                        int data = newEncryption.decryption(stoi(textLines.at(x)));
                        dec2.push_back(data);
                        progress++;
                    }
                    });

                thrd1.join();
                thrd2.join();

                for (vector<int>::iterator it = dec1.begin(); it != dec1.end(); it++) {
                    decryptedDATA.push_back(*it);
                }
                for (vector<int>::iterator it = dec2.begin(); it != dec2.end(); it++) {
                    decryptedDATA.push_back(*it);
                }
               
            }
            else {  //encryption
                for (int x = 0; x < filesize; x++) {
                    int data = newEncryption.encryption(buffer8_t[x]);
                    encryptedDATA.push_back(data);
                    progress++;
                }
            }      
   }  
    else if (encryptionType == 1) {
        BASICXOR_Algorithm newEncryption;  // BASICXOR_Algorithm class
        newEncryption.generateKey(prime1, prime2);

        if (option == -1) {  //decryption
            for (vector<string>::iterator it = textLines.begin(); it != textLines.end(); it++) {
                if (*it == "") break;
                int data = newEncryption.decryption(stoi(*it));
                decryptedDATA.push_back(data);
                progress++;
            }
        }
              else {  //encryption
                  for (int x = 0; x < filesize; x++) {
                      int data = newEncryption.encryption(buffer8_t[x]);
                      encryptedDATA.push_back(data);
                      progress++;
                  }
              }
          }
      else {
          cerr << "error on: FILEO::encrypt " << endl;
      }
}

int FILEO::getProgress() {
    return progress;
}

void FILEO::setopt(int opt) {
    this->option = opt;
}

void FILEO::setencry(int opt) {
    this->encryptionType = opt;
}

int isPrime(int prime) { //prime number controller
    if (prime == 0 || prime == 1) return 0;
    for (int x = 2; x <= prime / 2; ++x) {
        if (prime % x == 0)
            return 0;
    }
    cout << "Prime number generated." << endl;
    return 1;
}


// It will be more complicated than this!!
