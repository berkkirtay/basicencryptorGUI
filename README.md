## Basic encryptor-decryptor implementation with wxwidgets GUI.

- I refactored the old code I wrote in this project. I changed the way generating input for RSA algorithm. Now it takes 3 or 2 letters and put them in the same chunk of data. It is more secure but since it requires a huge computing power, it is advisable to use a block cipher algorithm when we handle big files. We can implement any of those algorithms but I developed this program for fun and we shouldn't expect a professional result. We should always use ready and tested cryptography libraries if we are serious about our encryption.

- We can encrypt all kinds of file types. It reads all the bytes in the file and saves the encrypted data in hex. If we increase the chunk size then we should also choose bigger primes.

## How to: 
Attention! You must have wxwidgets libs to compile source codes. I included a compiled executable file(windows) in the releases and I also included a cmake file for linux.

## Choosing the file to encrypt:
![Enc1](https://i.imgur.com/4O6wplR.png)

## Generated prime numbers:
![Enc2](https://i.imgur.com/oR8QUKg.png)

## Processed file:
![Enc3](https://i.imgur.com/cBjoSww.png)

