#ifndef RLE_H
#define RLE_H

#include "Cripto.h"
#include <string>

class RLE : public Cripto {
public:
    RLE() = default;
    std::string encode(const std::string &text, int key) override;
    std::string decode(const std::string &text, int key) override;
};

#endif 
