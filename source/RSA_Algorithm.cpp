#include "RSA_Algorithm.h"
RSA_Algorithm::RSA_Algorithm() {}  // Prime numbers should be big for a robust encryption. So, data can't be decrypted without knowing the key..

void RSA_Algorithm::generateKey(int prime1, int prime2) {
    integer N = prime1 * prime2;
    integer Qn = (prime1 - 1) * (prime2 - 1);

    //public key (e,N)
    integer e = 2;
    while (e < Qn) {  //for checking that e between -> 1 < e < Q(n) and greatestCommonDivisor(e, Q(n)) = 1, Hamming weight : 0x10001 
        if (greatestCommonDivisor(e, Qn) == 1 && e > 500) {  // Again e should be big in order to get a powerful encryption
            break;
        }
        else {
            e++;
        }
    }
    std::cout << "e: " << e << std::endl;
    publicKey = std::make_pair(e, N);
    //  std::cout << "public key (e,N) : " << publicKey.first << "," << publicKey.second << std::endl;

      //private key (d,N)
    integer d;
    integer k = 1;
    while (true) {
        k += Qn;
        if (greatestCommonDivisor(k, e) != 1) {
            d = k / e;
            break;
        }
    }
    privateKey = std::make_pair(d, N);
    std::cout << "d: " << d << std::endl;
    //  std::cout << "private key (e,N) : " << privateKey.first << "," << privateKey.second << std::endl;
}
integer RSA_Algorithm::encryption(int data) {
    integer xdata;
    xdata = 1;
    for (int x = 0; x < publicKey.first; x++) {
        xdata *= data;
        xdata %= publicKey.second;
    }
    return xdata;
    //  integer p = pow(data, publicKey.first);
    //  integer c = p % publicKey.second;
    //  return c;
}

integer RSA_Algorithm::decryption(int data) {
    integer xdata;
    xdata = 1;
    for (int x = 0; x < privateKey.first; x++) {
        xdata *= data;  // simply taking powers of data..
        xdata %= privateKey.second;
    }
    return xdata;
    //  long long p = pow(data, privateKey.first); We cannot do this operation with that way since d can take value like 227831 and cause overflow.
     // int m = p % privateKey.second;
     // return m;
}

integer RSA_Algorithm::greatestCommonDivisor(integer x, integer y) {
    integer c;
    while (true) {
        c = x % y;
        if (c == 0)
            return y;
        x = y;
        y = c;
    }
}