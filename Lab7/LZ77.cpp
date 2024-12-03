#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

struct Part {
    int pos;
    int length;
};

string LZ77(const string& input, int WindowMaxSize, int maxMatchLength) {
    string res;
    int currPos = 0;

    int inputSize = input.size();

    while (currPos < inputSize) {
        int matchLength = 0;
        int matchOffset = 0;

        int startOfWindow = max(0, currPos - WindowMaxSize);
        for (int i = startOfWindow; i < currPos; i++) {
            int j = 0;
            while (j < maxMatchLength && currPos + j < inputSize && input[i + j] == input[currPos + j]) {
                j++;
            }
            if (j > matchLength) {
                matchLength = j;
                matchOffset = currPos - i;
            }
        }

        if (matchLength > 1) {
            res += "[" + to_string(matchOffset) + "|" + to_string(matchLength) + "]";
        } else {
            res += input[currPos];
        }

        currPos += max(matchLength, 1);
    }

    return res;
}

string decompressedLz77(const string& compressed) {
    string decompressed;
    int currPos = 0;

    while (currPos < compressed.size()) {
        if (compressed[currPos] == '[') {

            size_t closeBracket = compressed.find(']', currPos);
            string match = compressed.substr(currPos + 1, closeBracket - currPos - 1);

            size_t separator = match.find('|');
            int offset = stoi(match.substr(0, separator));
            int length = stoi(match.substr(separator + 1));

            int start = decompressed.size() - offset;
            for (int i = 0; i < length; i++) {
                decompressed += decompressed[start + i];
            }

            currPos = closeBracket + 1;
        } else {

            decompressed += compressed[currPos];
            currPos++;
        }
    }

    return decompressed;
}

int main() {
    int maxWindowSize = 64;
    int maxMatchLength = 15;

    string s = "The compression and the decompression leave an impression. Hahahahaha!";
    string res = LZ77(s, maxWindowSize, maxMatchLength);

    
    cout << "Original " << s << "\n\n";
    
    cout << "Compressed  " << res << "\n\n";
    

    string decompressed = decompressedLz77(res);

    cout << "Decompressed " << decompressed << "\n\n";

}
