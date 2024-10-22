#include <iostream>
#include "CaesarCipher.h"
#include "ColumnarTranspositionCipher.h"
#include "RLE.h"

using namespace std;

int main() {
   
    CaesarCipher caesar; 
    string caesarText = "Hello, World!";
    int caesarKey = 3;  
    string caesarEncoded = caesar.encode(caesarText, caesarKey);
    string caesarDecoded = caesar.decode(caesarEncoded, caesarKey);

    cout << "Caesar Cipher Test:" << endl;
    cout << "Original: " << caesarText << endl;
    cout << "Encoded: " << caesarEncoded << endl;
    cout << "Decoded: " << caesarDecoded << endl << endl;

    
    ColumnarTranspositionCipher columnar; 
    string columnarText = "Hello world";
    int columnarKey = 2;  
    string columnarEncoded = columnar.encode(columnarText, columnarKey);
    string columnarDecoded = columnar.decode(columnarEncoded, columnarKey);

    cout << "Columnar Transposition Cipher Test:" << endl;
    cout << "Original: " << columnarText << endl;
    cout << "Encoded: " << columnarEncoded << endl;
    cout << "Decoded: " << columnarDecoded << endl << endl;

    
    RLE rle;
    string rleText = "AAABBBCCCCDDDDA";
    int rleKey = 0; 
    string rleEncoded = rle.encode(rleText, rleKey);
    string rleDecoded = rle.decode(rleEncoded, rleKey);

    cout << "RLE (Run-Length Encoding) Test:" << endl;
    cout << "Original: " << rleText << endl;
    cout << "Encoded: " << rleEncoded << endl;
    cout << "Decoded: " << rleDecoded << endl;
}