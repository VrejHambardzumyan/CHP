#include "ColumnarTranspositionCipher.h"
#include <stdexcept>

std::string ColumnarTranspositionCipher::encode(const std::string &text,int key) {
  
    int rows = (text.length() + key - 1) / key;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(key, ' '));
    
    int index = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < key; ++c) {
            if (index < text.length()) {
                matrix[r][c] = text[index++];
            }
        }
    }

    std::string encodedText;
    for (int c = 0; c < key; ++c) {
        for (int r = 0; r < rows; ++r) {
            encodedText += matrix[r][c];
        }
    }

    return encodedText;
}

std::string ColumnarTranspositionCipher::decode(const std::string &text, int key) {
   
    

    int rows = (text.length() + key - 1) / key;
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(key, ' '));

    int index = 0;
    for (int c = 0; c < key; ++c) {
        for (int r = 0; r < rows; ++r) {
            if (index < text.length()) {
                matrix[r][c] = text[index++];
            }
        }
    }

    std::string decodedText;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < key; ++c) {
            decodedText += matrix[r][c];
        }
    }

    return decodedText;
}

