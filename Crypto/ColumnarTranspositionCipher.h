#ifndef COLUMNARTRANSPOSITIONCIPHER_H
#define COLUMNARTRANSPOSITIONCIPHER_H

#include "Cripto.h"
#include <string>
#include <vector>

class ColumnarTranspositionCipher : public Cripto {
private:
    int columns;

public:
    ColumnarTranspositionCipher() = default;
    std::string encode(const std::string &text, int key) override;
    std::string decode(const std::string &text, int key) override;
};

#endif 
