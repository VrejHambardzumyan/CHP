#include <string>
#include <iostream>

class RLE {
public:
   
    static std::string encode(const std::string& input) {
        std::string encoded;
        int count = 1;

        for (size_t i = 0; i < input.size(); ++i) {
           
            while (i < input.size() - 1 && input[i] == input[i + 1]) {
                count++;
                i++;
            }
           
            encoded += input[i];
            encoded += std::to_string(count);
            count = 1;
        }

        return encoded;
    }
 
    static std::string decode(const std::string& input) {
        std::string decoded;
        for (size_t i = 0; i < input.size(); ++i) {
            char currentChar = input[i];
            i++; 

            std::string countStr;
           
            while (i < input.size() && isdigit(input[i])) {
                countStr += input[i];
                i++;
            }
            i--; 

            int count = std::stoi(countStr); 
            decoded += std::string(count, currentChar); 
        }

        return decoded;
    }
};

int main() {
    std::string input = "....    AASSS";
    std::string encoded = RLE::encode(input);
    std::string decoded = RLE::decode(encoded);

    std::cout << "Original: " << input << std::endl;
    std::cout << "Encoded: " << encoded << std::endl;
    std::cout << "Decoded: " << decoded << std::endl;

}

