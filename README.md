# ji-ve475-c2
## Table of Contents

- [Environment and software support of the project](#Environment and software support of the project)
- [Fuction of the project](#Fuction of the project)
- [Usage](#usage)

## Environment and software support of the project

- Environment: Ubuntu 16.04 (based on LINUX)
- Compilor: GNU GCC
- Additional library: [gmp](https://gmplib.org/) 
- IDE: codeblocks

## Fuction of the project

Implement a new cryptography. Do not learn from website or elsewhere directly, but a simple
application of Hash.

## Key generation

A pseudo-random string of 1671 bits. But it is fixed for one pair decryption and encryption.
  
  
##Encryption

First generate an array with min(501,3*length of plaintext) it will avoid some ciphertext 
too short and too easy to figure out the rule.
  
  The random key is used to determine the position in the new arrayof bit in plaintext,as code is 
  published in phase 3, you will find if the key is not run out it will 
  jump 19 each time if run out it will start at middle point to put plaintext.
  
  Finally when all the position in the array is filled (if no plaintext then add a random number),
  do addition with 197 power of index to get the cipher text.
  
  
##Decryption 
 First use the power of 197 to determine the length of array used in 
the encryption. Follow the same strategy in encryption to orderly get the position of related cipher 
plain pair bits. For each encrypted bit, calculate the according plain bit by
calculating the factor of related power of 197