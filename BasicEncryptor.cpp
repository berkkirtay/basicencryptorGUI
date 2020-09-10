#include "BasicEncryptor.h"



/* 
   THIS PROGRAM IS ONLY FOR EDUCATIONAL OR TRAINING. I'd keep improving this program.
   I used an algorithm like RSA and added XOR operator applying as well.
   I made a new basic algorithm implementation which uses 5 keychars to encrypt each character in the given line according to its value with XOR operator. It can be altered to get a harder encryption. 
   XOR operator is great for encryption because it flips the bits and gives old value after applying 2 times..
   Program's handling every character separately(it calculates new character every turn), so, it works a bit slowly if we try handling big files like mp4, zip, iso etc. Of course It's way too more suitable using with text files.
   Built by trantor00
*/
using namespace std; // standart library namespace


//definitions
FILEO::FILEO(string fileName, string outFileName, int opt) {
    this->fileName = fileName;
    this->outFileName = outFileName;
}
FILEO::~FILEO() {}

void FILEO::createKey(int key) {
     x += key % 13; key /= 13;
     x += key % 17; key /= 17;
     key *= x;
    while (true) {  //creating 2 prime numbers from the key given.  
        if(key>100) key /= 3;
        if (isPrime(x)) {
            y = key % 11;
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

void FILEO::readingFile() {
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
    cout << "File is reading, please wait." << endl;

    while (FILE) { //It's an object so we can look for if it exists or not!
        string *newLine = new string;
        getline(FILE, *newLine);
        textLines.push_back(*newLine); // pushing every new line in the list
        delete newLine;
    }
    FILE.close();
}
void FILEO::writingFile() {
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
    for (vector<string>::iterator it = textLines.begin(); it != textLines.end(); it++) {
        OUTFILE << *it << endl;
    }
    OUTFILE.close();
    cout << "\nTask Completed, File created as " << outFileName << endl;
}
bool isValidChar(char CHAR) {
    bool isValid;
    if (CHAR >= 2 && CHAR <= 126)  isValid = true;
    else isValid = false;
   return isValid;
}

void FILEO::lineEncrypt(string& line, int prime1, int prime2, int option, int row) {  // We can change this encryption algorithm whatever way we want..
    int N = prime1 * prime2;
    int Qn = (prime1 - 1) * (prime2 - 1);
    int temp;
    row++;
    //public key
    int e = 2;
    while (e < Qn && e != prime1 && e != prime2) {  //for checking that e between -> 1 < e < Q(n) and greatestCommonDivisor(e, Q(n)) = 1
        temp = greatestCommonDivisor(e, Qn);
        if (temp == 1)
            break;
        else
            e++;
    }
    int c = e * Qn; 

    //key characters
   /* char keys[5] = {
        prime1,
        prime2,
        Qn%3,
        e,
        c      
   }; */


    vector<char> keys;   // a more complicated and difficult way to encrypt.
     for (int j = 0; j < line.length(); j++) {
         int key = 0;
         if (j % 5 == 0) key = prime1 / (prime1 % row + 1);
         else if (j % 5 == 1) key = prime2 / (prime2 % row + 1);
         else if (j % 5 == 2) key = Qn % (row % j + 1);
         else if (j % 5 == 3) key = e % (j + 1) + row % e;
         else key = c % (row % j + 1);
         keys.push_back(key);
     }

    // XOR operations 
    for (int x = 0; x < line.length(); x++) {   //encryption every char on the string line..
        if (option == -1)  line[x] = line[x] ^ keys.at(x); // if (!isValidChar(line[x]))
        else  line[x] = line[x] ^ keys.at(x); // if (isValidChar(!line[x])) 

        //line[x] = line[x] ^ keys[x % 5];
    }
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
    int j = 0;
    for (vector<string>::iterator it = textLines.begin(); it != textLines.end(); it++) {
        lineEncrypt(*it, prime1, prime2, option, j);
        j++;
        int u = (j * 100) / textLines.size();
        progress += u;
    }
}
int FILEO::getProgress() {
    return progress;
}

int greatestCommonDivisor(int x, int y) {
    int c;
    while (true) {
        c = x % y;
        if (c == 0)
            return y;
        x = y;
        y = c;
    }
}

int isPrime(int prime) { //prime number controller
    if (prime == 0 || prime==1) return 0;
    for (int x = 2; x <= prime/2; ++x){
        if (prime % x == 0)
            return 0;
    }
    cout << "Prime number generated." << endl;
    return 1;
}


// It will be more complicated than this!!