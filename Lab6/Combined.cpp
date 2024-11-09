#include <iostream>
#include <string>
#include <vector>

using namespace std;


class CaesarCipher {
private:
    static const int ASCII_START = 0;
    static const int ASCII_END = 255;
    static const int ASCII_RANGE = ASCII_END - ASCII_START + 1;

    int normalizeShift(int shift) {
        return (shift % ASCII_RANGE + ASCII_RANGE) % ASCII_RANGE;
    }

public:
    string encode(const string &text, int shift) {
        string encodedText = "";
        int normalizedShift = normalizeShift(shift);

        for (char c : text) {
            if (c >= ASCII_START && c <= ASCII_END) {
                char encodedChar = ASCII_START + (c - ASCII_START + normalizedShift) % ASCII_RANGE;
                encodedText += encodedChar;
            } else {
                encodedText += c;
            }
        }

        return encodedText;
    }

    string decode(const string &text, int shift) {
        string decodedText = "";
        int normalizedShift = normalizeShift(shift);

        for (char c : text) {
            if (c >= ASCII_START && c <= ASCII_END) {
                char decodedChar = ASCII_START + (c - ASCII_START - normalizedShift + ASCII_RANGE) % ASCII_RANGE;
                decodedText += decodedChar;
            } else {
                decodedText += c;
            }
        }

        return decodedText;
    }
};


class ColumnarTranspositionCipher {
private:
    string text;
    int columns;

public:
    ColumnarTranspositionCipher(const string& inputText, int col) : text(inputText), columns(col) {}

    string encode() {
        int rows = (text.length() + columns - 1) / columns;
        vector<vector<char>> matrix(rows, vector<char>(columns, ' '));
        int index = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (index < text.length()) {
                    matrix[r][c] = text[index++];
                }
            }
        }

        string encodedText;
        for (int c = 0; c < columns; ++c) {
            for (int r = 0; r < rows; ++r) {
                encodedText += matrix[r][c];
            }
        }

        return encodedText;
    }

    string decode() {
        int rows = (text.length() + columns - 1) / columns;
        vector<vector<char>> matrix(rows, vector<char>(columns, ' '));
        int index = 0;

        for (int c = 0; c < columns; ++c) {
            for (int r = 0; r < rows; ++r) {
                if (index < text.length()) {
                    matrix[r][c] = text[index++];
                }
            }
        }

        string decodedText;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                decodedText += matrix[r][c];
            }
        }

        return decodedText;
    }
};


class CombinedCipher {
private:
    CaesarCipher caesar;
    ColumnarTranspositionCipher* columnar; 

public:
    CombinedCipher() : columnar(nullptr) {}

    string encode(const string& text, int shift, int columns) {
       
        string caesarEncoded = caesar.encode(text, shift);
        
      
        columnar = new ColumnarTranspositionCipher(caesarEncoded, columns);
        string columnarEncoded = columnar->encode();

        return columnarEncoded;
    }

    string decode(const string& text, int shift, int columns) {
        
        columnar = new ColumnarTranspositionCipher(text, columns);
        string columnarDecoded = columnar->decode();

       
        string caesarDecoded = caesar.decode(columnarDecoded, shift);

        return caesarDecoded;
    }

    ~CombinedCipher() {
        delete columnar;
    }
};


int main() {
    CombinedCipher cipher;
    string text = "HELLO WORLD ";
    int caesarShift = 3;
    int columns = 4;

    string encodedText = cipher.encode(text, caesarShift, columns);
    cout << "Encoded Text: " << encodedText << endl;

    string decodedText = cipher.decode(encodedText, caesarShift, columns);
    cout << "Decoded Text: " << decodedText << endl;

    
}
