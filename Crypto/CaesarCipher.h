#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "Cripto.h"
#include <string>

class CaesarCipher : public Cripto {
private:
    static const int ASCII_START = 0;  
    static const int ASCII_END = 255; 
    static const int ASCII_RANGE = 256;

    int normalizeShift(int shift);

public:
    CaesarCipher() = default;
    std::string encode(const std::string &text,  int key) override;
    std::string decode(const std::string &text, int key) override;
};

#endif
