#ifndef CRIPTO_H
#define CRIPTO_H

#include <string>

class Cripto {
public:
    virtual ~Cripto() = default;
    virtual std::string encode(const std::string &text,  int key) = 0;
    virtual std::string decode(const std::string &text,  int key) = 0;
};

#endif
