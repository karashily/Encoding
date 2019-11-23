# Huffman and Arithmetic Coding
Huffman and Arithmetic encoding techniques implemented in C++.
Use g++ for compilation.

### Prerequisites

* g++
```sh
apt-get install g++
```

## Huffman Coding

### Methods
  - entropy: to calculate entropy of the message/image
  - tree: build huffman tree for the message/image
  - encode: encode using huffman coding. has 2 modes: normal encoding and corelation encoding (add a -c parameter at the end)

### Installation

1. Build the file using the makefile by simply opening the shell and typing:
```sh
make
```
  or Build using g++ by typing:
```sh
g++ huffman.cpp headers/huffman.cpp -o huffman.exe
```
2. Run the program
```sh
huffman.exe -encode < file.pgm > out.txt
```


## Arithmetic Coding

### Methods
  - encode: encode an image/message using arithmetic coding
  - decode: decode an encoded image
  - bin_to_dec: convert a binary number (max 32 bits) to decimal
  - dec_to_bin: convert a decimal number to binary (max 32 bits)
   
### Installation

1. Build the file using the makefile by simply opening the shell and typing:
```sh
make
```
  or Build using g++ by typing:
```sh
g++ arithmetic.cpp headers/arithmetic.cpp -o arithmetic.exe
```
2. Run the program
```sh
arithmetic -encode < file.pgm > out.txt
```
