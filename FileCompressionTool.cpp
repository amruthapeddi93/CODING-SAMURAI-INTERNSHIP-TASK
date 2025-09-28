#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left, * right;
    Node(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

// Comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman Codes by traversing tree
void generateCodes(Node* root, string code, unordered_map<char, string>& huffCodes) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffCodes[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffCodes);
    generateCodes(root->right, code + "1", huffCodes);
}

// Decode encoded string
string decodeString(Node* root, string encoded) {
    string decoded = "";
    Node* curr = root;
    for (char bit : encoded) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}

int main() {
    string text;
    cout << "Enter text to compress: ";
    getline(cin, text);

    // Frequency table
    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    // Priority queue (min-heap)
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();

    // Generate Huffman Codes
    unordered_map<char, string> huffCodes;
    generateCodes(root, "", huffCodes);

    cout << "\nHuffman Codes:\n";
    for (auto pair : huffCodes) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    // Encode
    string encoded = "";
    for (char c : text) encoded += huffCodes[c];
    cout << "\nEncoded Text: " << encoded << "\n";

    // Decode
    string decoded = decodeString(root, encoded);
    cout << "Decoded Text: " << decoded << "\n";

    return 0;
}
