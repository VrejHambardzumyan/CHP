#include <iostream>
#include <cstring>
using namespace std;

class VigenereCipher {
public:
    void encode(const char str[], const char key[], char encoded[]) {
        int strLen = strlen(str);

        for (int i = 0; i < strLen; i++) {
            int strIndex = findIndex(str[i]);
            int keyIndex = findIndex(key[i]);

            encoded[i] = Alphabet[(strIndex + keyIndex) % 26];
        }
        encoded[strLen] = '\0';  
    }
  
    void decode(const char encoded[], const char key[], char decoded[]) {
        int strLen = strlen(encoded);

        for (int i = 0; i < strLen; i++) {
            int encIndex = findIndex(encoded[i]);
            int keyIndex = findIndex(key[i]);

            decoded[i] = Alphabet[(encIndex - keyIndex + 26) % 26];  
        }
        decoded[strLen] = '\0';  
    }

private:
    const char* Alphabet = "abcdefghijklmnopqrstuvwxyz";
    int findIndex(char c) {
        for (int j = 0; j < 26; j++) {
            if (c == Alphabet[j]) {
                return j;
            }
        }
        return -1; 
    }
};

int main() {
    char str[1000], key[1000];

    cout << "Enter string: ";
    cin >> str;

    cout << "Enter key of the same length as the string: ";
    cin >> key;

    char encoded[1000], decoded[1000];

    VigenereCipher cipher;
 
    cipher.encode(str, key, encoded);
    cout << "Encoded: " << encoded << endl;

    cipher.decode(encoded, key, decoded);
    cout << "Decoded: " << decoded << endl;
}
