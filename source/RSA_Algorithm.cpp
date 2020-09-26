#include "RSA_Algorithm.h"
RSA_Algorithm::RSA_Algorithm() {}  // If prime numbers are too great then it'd take time to encrypt but it's almost can't be decrypted without knowing the key..

void RSA_Algorithm::generateKey(int prime1, int prime2) {
    int N = prime1 * prime2;
    int Qn = (prime1 - 1) * (prime2 - 1);
    int temp;
    //public key (e,N)
    int e = 2;
    while (e < Qn && e != prime1 && e != prime2) {  //for checking that e between -> 1 < e < Q(n) and greatestCommonDivisor(e, Q(n)) = 1
        temp = greatestCommonDivisor(e, Qn);
        if (temp == 1)
            break;
        else
            e++;
    }
    publicKey = std::make_pair(e, N);
  //  std::cout << "public key (e,N) : " << publicKey.first << "," << publicKey.second << std::endl;

    //private key (d,N)
    int d;
    int k = 1;
    while (true) {
        k = k + Qn;
        if (k % e == 0) {
            d = (k / e);
            break;
        }
    }
    privateKey = std::make_pair(d, N);
  //  std::cout << "private key (e,N) : " << privateKey.first << "," << privateKey.second << std::endl;
}
int RSA_Algorithm::encryption(int data) {
    int current, xdata;
    current = data;
    xdata = 1;
    for (int x = 0; x < publicKey.first; x++){
        xdata *= current;
        xdata %= publicKey.second;
    }
    data = xdata;
    return data;
}

int RSA_Algorithm::decryption(int data) {
    int current, xdata;
    current = data;
    xdata = 1;
    for (int x = 0; x < privateKey.first; x++){
        xdata *= current;
        xdata %= privateKey.second;
    }
    data = xdata;
    return data;
}

int RSA_Algorithm::greatestCommonDivisor(int x, int y) {
    int c;
    while (true) {
        c = x % y;
        if (c == 0)
            return y;
        x = y;
        y = c;
    }
}