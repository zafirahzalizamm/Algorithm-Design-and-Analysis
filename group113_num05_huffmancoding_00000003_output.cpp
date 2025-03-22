
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <bitset>
#include <algorithm>
#include <chrono>

using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char ch, int freq) : data(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// to create codewords
void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == nullptr)
        return;

    if (root->data != '#') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);   // if root to left, codeword is 0
    generateCodes(root->right, code + "1", codes);  // if root to right, codeword is 1
}

// to build the Huffman Tree
Node* buildHuffmanTree(map<char, int>& frequencies) {
    auto cmp = [](Node* a, Node* b) { return a->frequency > b->frequency; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);

    for (auto& pair : frequencies) {
        Node* newNode = new Node(pair.first, pair.second);
        pq.push(newNode);
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* internalNode = new Node('#', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    return pq.top();
}

// to read the input text file and print it to output text file
void encodeFile(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);    // read from files
    ofstream fout(outputFile);  // write on files

    // Start measuring execution time
    auto startTime = std::chrono::high_resolution_clock::now();

    // Error message when file not found
    if (!fin || !fout) {
        cout << "Error opening file." << endl;
        return;
    }

    // total number of unique characters
    int numUniqueChars;
    fin >> numUniqueChars;
    fout << numUniqueChars << endl;

    map<char, int> frequencies;
    char ch;
    for (int i = 0; i < numUniqueChars; i++) {
        fin >> ch;
        frequencies[ch] = 0;
    }

    string word;
    getline(fin, word); // Consume the newline character after reading numUniqueChars

    //  total frequencies of each unique characters
    while (fin >> word) {
        for (char c : word) {
            frequencies[c]++;
        }
    }

    vector<Node*> nodes;
    for (auto& pair : frequencies) {
        nodes.push_back(new Node(pair.first, pair.second));
    }

    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) { return a->frequency < b->frequency; });

        Node* left = nodes[0];
        Node* right = nodes[1];

        Node* internalNode = new Node('#', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        nodes.erase(nodes.begin(), nodes.begin() + 2);
        nodes.push_back(internalNode);
    }

    Node* root = nodes[0];

    map<char, string> codes;
    generateCodes(root, "", codes);

    vector<pair<char, int>> charFreqPairs;
    for (auto& pair : frequencies) {
        charFreqPairs.push_back(pair);
    }

    sort(charFreqPairs.begin(), charFreqPairs.end());

    int totalBits = 0;
    int encodedBits = 0;
    for (auto& pair : charFreqPairs) {
        fout << pair.first << " " << pair.second << " " << codes[pair.first] << " " << codes[pair.first].length() * pair.second << endl;
        totalBits += codes[pair.first].length() * pair.second;
        encodedBits += pair.second;
    }

    int totalFrequencies = 0;
    for (auto& pair : frequencies) {
        totalFrequencies += pair.second;
    }
    int totalSpace = (totalBits * 100) / (totalFrequencies * 7);

    fout << totalBits << "-bit out of " << totalFrequencies * 7 << "-bit" << endl;  // total bits out of total frequencies
    fout << "total space " <<  totalSpace << "%" << endl;   // percentage of total space

    // Stop measuring execution time
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    double time = duration.count() / 1000.0; // Convert milliseconds to seconds

    fout << time << "s" << endl;    // time taken to finish the program from start to end

    fin.close();
    fout.close();
}

int main() {
    string inputFile = "huffmancoding_00000003_input.txt";      // inputFile
    string outputFile = "huffmancoding_00000003_output.txt";    // outputFile

    encodeFile(inputFile, outputFile);

    return 0;
}
