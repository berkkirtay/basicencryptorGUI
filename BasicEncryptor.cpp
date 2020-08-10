#include "BasicEncryptor.h"

// CAUTION : USING THIS PROGRAM IS AT YOUR OWN RISK! PLEASE DON'T USE WITH IMPORTANT FILES.
// THIS PROGRAM IS ONLY FOR EDUCATIONAL OR TRAINING. I'd keep improving this program(it's still very basic)..
// I will use an algorithm like RSA algorithm. I altered it because of handling big files.
// Program's handling every character separately(it calculates new character every turn), so, it works a bit slowly if we try handling big files like mp4, zip, iso etc. Of course It's way too more suitable using with text files.
// Built by trantor00
using namespace std; // standart library namespace


//main function
int main() {
    startingMsg();
    return 0; //program finished 
}

//definitions
FILEO::FILEO(string* fileName, string* outFileName, int opt) {
    textLines = new vector<string>;  //allocating memory for vector..
    this->fileName = fileName;
    this->outFileName = outFileName;
}
FILEO::~FILEO() {}

void FILEO::createKey(int key) {
    x = key % 3 + key % 7;

    while (true) {  //creating 2 prime numbers from the key given.        
        if (isPrime(x)) {
            key /= 10;
            y = key % 7;
            while (true) {
                if (isPrime(y) && y != x)  break;
                else y++;
            }
            break;
        }
        else  x++;
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
        FILE.open(*fileName, ios::in | ios::binary);  //input file!!!!  
        if (!FILE)
            throw "File can't be opening!";
    }
    catch (exception& e) {
        cout << "FILE HANDLING ERROR: " << e.what() << endl;
        system("pause");
    }
    cout << "File is reading, please wait." << endl;

    while (FILE) { //It's an object so we can look for if it exists or not!
        string* newLine = new string;
        getline(FILE, *newLine);
        textLines->push_back(*newLine); // pushing every new line in the list
    }
    FILE.close();
}
void FILEO::writingFile() {
    fstream OUTFILE;
    try {
        OUTFILE.open(*outFileName, ios::out | ios::binary);
        if (!OUTFILE)
            throw "File can't be opening!";
    }
    catch (exception& e) {
        cout << "FILE HANDLING ERROR: " << e.what() << endl;
        system("pause");
    }
    for (vector<string>::iterator it = textLines->begin(); it != textLines->end(); it++) {
        OUTFILE << *it << endl;
    }
    OUTFILE.close();
    cout << "\nTask Completed, File created as " << *outFileName << endl;
}
/*bool isValidChar(char CHAR) {
    bool isValid;
    if (CHAR >= 2 && CHAR <= 126)  isValid = true;
    else isValid = false;
   return isValid;
}*/

void FILEO::lineEncrypt(string& line, int prime1, int prime2, int option) {  // We can change this encryption algorithm whatever way we want..
    int N = prime1 * prime2;
    int Qn = (prime1 - 1) * (prime2 - 1);
    int temp;
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
    if (N == 0) N++;
    c = c / N;
    c = (c * 2 - 1) * (line.length() % 5);
    //  if (c < 0) c *= -1;
    for (int x = 0; x < line.length(); x++) {   //encryption every char on the string line..
        if (option == -1)  line[x] -= c; // if(!isValidChar(line[x])) line[x] += c; 
        else  line[x] += c; // if(isValidChar(!line[x])) line[x] -= c; 
    }
}
void FILEO::encrypt(int prime1, int prime2, int option) {
    string tempName = *fileName;
    for (int a = 0; a < tempName.length(); a++) {  // for the same file extension output..
        if (tempName[a] == '.') {
            for (int j = a; j < tempName.length(); j++) {
                outFileName->push_back(tempName[j]);
            }
            break;
        }
    }
    int j = 0;
    for (vector<string>::iterator it = textLines->begin(); it != textLines->end(); it++) {
        lineEncrypt(*it, prime1, prime2, option);
        j++;
        int u = (j * 100) / textLines->size();
        for (int k = 0; k < u; k++)
            if (u % 10 == 0 && u % 6 == 0) cout << "Processing %" << u << endl; // very basic load-bar
    }
    cout << "Processing %100" << endl;
}
void startingMsg() {
    cout << "CAUTION : USING THIS PROGRAM IS AT YOUR OWN RISK! PLEASE DON'T USE WITH IMPORTANT FILES." << endl;
    cout << "Welcome! This program is built for encryption files.\nIt's more efficient with smaller files.\nProgram encrypts with a small amount of mistake (but you'd lose your data!!!) when you try with big files!" << endl;
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
    int cont = 0;
    int j = prime / 2;
    for (int x = 2; x <= j; x++)
    {
        if (prime % x == 0)
            return 0;
    }
    cout << "Prime number generated." << endl;
    return 1;
}


// It will be more complicated than this!!