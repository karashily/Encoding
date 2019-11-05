# Huffman and Arithmetic Coding
Huffman and Arithmetic encoding techniques implemented in C++.
Use g++ for compilation.


Huffman Coding methods:
  - entropy: to calculate entropy of the message/image
  - tree: build huffman tree for the message/image
  - encode: encode using huffman coding. has 2 modes: normal encoding and corelation encoding (add a -c parameter at the end)
  
  ex for use:
   - g++ huffman.cpp headers/huffman.cpp -o huffman.exe
   - huffman.exe -encode < file.pgm > out.txt

Arithmetic Coding methods:
  - encode: encode an image/message using arithmetic coding
  - decode: decode an encoded image
  - bin_to_dec: convert a binary number (max 32 bits) to decimal
  - dec_to_bin: convert a decimal number to binary (max 32 bits)
  
  ex for use:
   - g++ arithmetic.cpp headers/arithmetic.cpp -o arithmetic.exe
   - arithmetic -encode < file.pgm > out.txt
   
