#include "RSA_Algorithm.h"

using namespace RSA_;

RSA_Algorithm::RSA_Algorithm() {}  
// Prime numbers should be big for a robust encryption. So, data canott be decrypted without knowing the key..

void RSA_Algorithm::generateKey(int prime1, int prime2) {
    integer p1 = static_cast<integer>(prime1);
    integer p2 = static_cast<integer>(prime2);
    integer N = p1 * p2;
    integer Qn = (p1 - 1) * (p2 - 1);

    //public key (e,N)
    //for checking that e between -> 1 < e < Q(n) and greatestCommonDivisor(e, Q(n)) = 1.

    integer e = 2;
    while (e < Qn) {  
        if (greatestCommonDivisor(e, Qn) == 1 && e > 100) {  
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
integer RSA_Algorithm::encryption(integer data) {
    data = basicXOR(data, 1);
    integer xdata = 1;
    for (int x = 0; x < publicKey.first; x++) {
        xdata *= data;
        xdata %= publicKey.second;
    }
    return xdata;
}

integer RSA_Algorithm::decryption(integer data) {
    integer xdata = 1;
    for (int x = 0; x < privateKey.first ; x++) {
        xdata *= data;  // simply taking powers of the data..
        xdata %= privateKey.second;
    }
    xdata = basicXOR(xdata, 0);
    return xdata;
    //We cannot do this operation with that way since d can take a value like 227831 and cause an overflow.
    /*long long p = pow(data, privateKey.first); 
      int m = p % privateKey.second;
      return m; */
}

integer RSA_Algorithm::basicXOR(integer data, int opt) {
    int defaultHash = 0xF0A12B;
    defaultHash = (defaultHash + (publicKey.first % 100)) % publicKey.first;
    if (opt == 0) {
        data ^= publicKey.first - 1;
        data /= defaultHash;
    }
    else {
        data *= defaultHash;
        data ^= publicKey.first - 1;
    }
    return data;
}

integer RSA_Algorithm::greatestCommonDivisor(integer x, integer y) {  // Euclidean algorithm
    integer c;
    while (true) {
        c = x % y;
        if (c == 0)
            return y;
        x = y;
        y = c;
    }
}
