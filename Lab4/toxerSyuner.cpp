#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

    void displayEncodedText() {
        string encoded = encode();
        cout << "Original Text: " << text << endl;
        cout << "Encoded Text: " << encoded << endl;
    }
};

int main() {
    string text;
    int columns;

    cout << "Enter the text to encode: ";
    cin >> text;
    
    cout << "Enter the number of columns: ";
    cin >> columns;

  
    ColumnarTranspositionCipher cipher(text, columns);
    cipher.displayEncodedText();
}
