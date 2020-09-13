#include "BasicEncryptor.h"

/*
   THIS PROGRAM IS ONLY FOR EDUCATIONAL OR TRAINING. I'd keep improving this program.
   This time I used exact RSA Algorithm to strengthen encryption. I'd add XOR as well.
   Program's handling every character separately(it calculates new character every turn), 
   so, it works a bit slowly if we try handling big files like mp4, zip, iso etc. Of course It's way too more suitable using with text files.
   Built by trantor00
*/
using namespace std; // standart library namespace

//definitions
FILEO::FILEO(string fileName, string outFileName, int opt) {
    this->fileName = fileName;
    this->outFileName = outFileName;   
}

void FILEO::createKey(int key) {  // prime number generator
    x += key % 51; key /= 13;
    x += key % 67;
    key *= x;
    y += (key % x);
    while (true) {  //creating 2 prime numbers from the key given.  
        y += key % 3;
        if (isPrime(x)) {
            y += key % x;
            while (true) {
                if (isPrime(y) && y != x)  break;
                else y++;
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
    try {
        FILE.open(fileName, ios::in | ios::binary);  //input file!!!!  
        if (!FILE)
            throw "File can't be opening!";
    }
    catch (exception& e) {
        cout << "FILE HANDLING ERROR: " << e.what() << endl;
        system("pause");
    }
    while (FILE) { //It's an object so we can look for if it exists or not!
        string newLine;
        getline(FILE, newLine);
        textLines.push_back(newLine); // pushing every new line in the list
    }
    FILE.close();
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
            OUTFILE << (char)*it;
        }
    }
    else {
        for (vector<int>::iterator it = encryptedDATA.begin(); it != encryptedDATA.end(); it++) {
          OUTFILE << *it << endl;
        }
    }
    OUTFILE.close();
}
/*bool isValidChar(char CHAR) {
    bool isValid;
    if (CHAR >= 2 && CHAR <= 126)  isValid = true;
    else isValid = false;
    return isValid;
}*/

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
    int j = 0;

    RSA_Algorithm newEncryption;  // RSA_Algorithm class
    newEncryption.generateKey(prime1, prime2);

    for (vector<string>::iterator it = textLines.begin(); it != textLines.end(); it++) {
        if (option == -1) {  //decryption
            if (*it == "") break;
            int data = newEncryption.decryption(stoi(*it));
            decryptedDATA.push_back(data);
        }
        else {  //encryption
            for (int x = 0; x < it->length(); x++) {
                int data = newEncryption.encryption(it->at(x));
                encryptedDATA.push_back(data);
            }
        }    
        j++;
        int u = (j * 100) / textLines.size();
        progress += u;
    }
}
int FILEO::getProgress() {
    return progress;
}

void FILEO::setopt(int opt) {
    this->option = opt;
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