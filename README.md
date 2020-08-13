Basic encryptor wxwidgets GUI version 
 
I used an algorithm like RSA and added XOR operator applying as well.
I made a new basic algorithm implementation which uses 5 keychars to encrypt each character in the given line according to its value with XOR operator. It can be altered to get a harder encryption. 
XOR operator is great for encryption because it flips the bits and gives old value after applying 2 times..
Program's handling every character separately(it calculates a new character every turn and it takes advantage of row number as well), so, it works a bit slowly if we try handling big files like mp4, zip, iso etc. Of course It's way too more suitable using with text files.

