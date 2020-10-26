## Basic encryptor-decryptor implementation with wxwidgets GUI Built by trantor00

This time I used exact RSA Algorithm to strengthen encryption. RSA_Algorithm class handles encryption and encrypted files consist only numbers anymore.
I'd add XOR as well for additional encryption security.

I also solved some memory leak problems..
Again program handles every character separately and applies RSA. 

From now on the program can encrypt all types of files(though it's a little slow..)! 


Attention! You must have wxwidgets libs to compile source codes. I included a compiled executable file(windows) in the releases and also included a cmake file so you can build it on the linux easily.

## How to: 
You only choose a file and encrytion type! Then you can encrypt or decrypt it with your key.

## Choosing the encryption type
![Enc1](https://i.imgur.com/4O6wplR.png)

## Generated prime numbers
![Enc2](https://i.imgur.com/Jzy5zT7.png)

## Processed file
![Enc3](https://i.imgur.com/cBjoSww.png)

