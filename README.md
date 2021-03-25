## Basic encryptor-decryptor implementation with wxwidgets GUI Built by trantor00

RSA_Algorithm class handles encryption and encrypted files consist only numbers now.
The program handles every character separately and applies RSA after creating a basic hash function for every character.

This program can encrypt all kinds of file types. For additional security you can change the prime generator algorithm to get much bigger prime numbers and try to use a block cipher algorithm.

BASICXOR_Algorithm class has a very weak algorithm and it shouldn't be used for encrption purposes. I only added it as an addition to the program. But I may remove it from the project in the future.

## How to: 
Attention! You must have wxwidgets libs to compile source codes. I included a compiled executable file(windows) in the releases and also included a cmake file so you can build it on linux easily.

You should choose a file and an encrytion type! Then you can encrypt or decrypt it with your key.

## Choosing the encryption type
![Enc1](https://i.imgur.com/4O6wplR.png)

## Generated prime numbers
![Enc2](https://i.imgur.com/oR8QUKg.png)

## Processed file
![Enc3](https://i.imgur.com/cBjoSww.png)

