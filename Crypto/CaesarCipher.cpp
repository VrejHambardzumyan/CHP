#include "CaesarCipher.h"
#include <stdexcept>

int CaesarCipher::normalizeShift(int shift) {
    return (shift % ASCII_RANGE + ASCII_RANGE) % ASCII_RANGE;
}

std::string CaesarCipher::encode(const std::string &text, int key) {

   
    int normalizedShift = normalizeShift(key);
    
    std::string encodedText;
    for (char c : text) {
        if (c >= ASCII_START && c <= ASCII_END) {
            char encodedChar = (c + normalizedShift) % ASCII_RANGE;
            encodedText += encodedChar;
        } else {
            encodedText += c;
        }
    }

    return encodedText;
}

std::string CaesarCipher::decode(const std::string &text,  int key) {
    
    int normalizedShift = normalizeShift(key);

    std::string decodedText;
    for (char c : text) {
        if (c >= ASCII_START && c <= ASCII_END) {
            char decodedChar = (c - normalizedShift + ASCII_RANGE) % ASCII_RANGE;
            decodedText += decodedChar;
        } else {
            decodedText += c;
        }
    }

    return decodedText;
}

