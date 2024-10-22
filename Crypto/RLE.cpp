#include "RLE.h"

std::string RLE::encode(const std::string &text, int key) {
    (void)key;  
    std::string encoded;
    int count = 1;

    for (size_t i = 1; i <= text.size(); ++i) {
        if (i < text.size() && text[i] == text[i - 1]) {
            ++count;
        } else {
            encoded +=  text[i - 1] +  std::to_string(count);
            count = 1;
        }
    }

    return encoded;
}

std::string RLE::decode(const std::string &text, int key) {
    (void)key;  
    std::string decoded;
    int count = 0;

    for (size_t i = 0; i < text.size(); ++i) {
        if (isdigit(text[i])) {
            count = count * 10 + (text[i] - '0');
        } else {
            decoded.append(count, text[i]);
            count = 0;
        }
    }

    return decoded;
}
