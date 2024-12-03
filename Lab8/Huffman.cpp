#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) codes[root->ch] = code;
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

string decompress(Node* root, const string& encoded) {
    string decoded = "";
    Node* current = root;
    for (char bit : encoded) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) { 
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

void huffman(string text) {
  
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;
    
    
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto p : freq) pq.push(new Node(p.first, p.second));
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* node = new Node('\0', left->freq + right->freq);
        node->left = left;
        node->right = right;
        pq.push(node);
    }
    Node* root = pq.top();
    
   
    unordered_map<char, string> codes;
    generateCodes(root, "", codes);
    
   
    string encoded = "";
    for (char ch : text) encoded += codes[ch];
    
 
    for (auto p : codes) cout << p.first << ": " << p.second << endl;
    cout << "Encoded " << encoded << endl;
    
   
    string decoded = decompress(root, encoded);
    cout << "Decoded " << decoded << endl;
}

int main() {
    string text;
    cout << "Enter text ";
    getline(cin, text);
    huffman(text);
}
