#include <iostream>
#include <string>
using namespace std;

class CaesarCipher 
{
private:
     
    static const int ASCII_START = 0;  
    static const int ASCII_END = 255; 
    static const int ASCII_RANGE = 256;

    
    int normalizeShift(int shift) {
        return (shift % ASCII_RANGE + ASCII_RANGE) % ASCII_RANGE;
    }

public:
    string encode(const string &text, int shift) {
        string encodedText = "";
        int normalizedShift = normalizeShift(shift);

        for (char c : text) 
        {
            if (c >= ASCII_START && c <= ASCII_END) 
            {
                char encodedChar = (c + normalizedShift) % ASCII_RANGE;
                encodedText += encodedChar;
            } else {
                encodedText += c;
            }
        }

        return encodedText;
    }

    string decode(const string &text, int shift) 
    {
        string decodedText = "";
        int normalizedShift = normalizeShift(shift);

        for (char c : text) 
        {
            if (c >= ASCII_START && c <= ASCII_END) 
            {
                char decodedChar =(c - normalizedShift + ASCII_RANGE) % ASCII_RANGE;
                decodedText += decodedChar;
            } else {
                decodedText += c;
            }
        }

        return decodedText;
    }
};

int main() {
    CaesarCipher cipher;

    string text = "!";
    int shift = 230;

    string encoded = cipher.encode(text, shift);
    cout << "Encoded: " << encoded << endl;

    string decoded = cipher.decode(encoded, shift);
    cout << "Decoded: " << decoded << endl;

}
