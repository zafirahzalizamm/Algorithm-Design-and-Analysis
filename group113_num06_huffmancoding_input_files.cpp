
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

/*****************************************************************
This function is to generate the random input file for Huffman
The random seed number is the group leader student id:
Muhammad Nafis Zahran (1201201241)
******************************************************************/

void generateRandomInput(string outputFile, int vertices) {

    const int charMax = 26;
    char alpha[charMax] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                            'H', 'I', 'J', 'K', 'L', 'M', 'N',
                            'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                            'V', 'W', 'X', 'Y', 'Z' };

    // to create and write an output file
    ofstream outfile;
    outfile.open(outputFile);

    // to set a fixed seed value & generate the same sequence of random number
    srand(1201201241); // Nafis's student ID (Group leader)

    int num = rand() % 26;
    outfile << num << endl;

    // Shuffle the alpha array to avoid repeated alphabets
    for (int i = charMax - 1; i > 0; i--) { //assign i to the last element in array
        int j = rand() % (i + 1); //assign find another random element in index j
        swap(alpha[i], alpha[j]); // suffle the element
    }

    // Write the alphabet to the file
    for (int i = 0; i < num; i++) {
        char character = alpha[i]; // write the element at index i to the file
        outfile << character << endl;
    }

    // generate input file algorithm
    srand(time(NULL));    // initialize the random number generator
    for (int i = 0; i < vertices; i++) { // generate number of input data lines
        int loop = 0;
        while (loop < 5) { //generate sequence of 5 characters
            int r = rand() % num;   // generate a random index num within the num
            char character = alpha[r];    // find the element at index r in character element
            outfile << character; // write into the file
            loop++;
        }
        outfile << " "; // space between input number lines
        loop = 0;
    }
    outfile.close();
}

/*****************************************************************
Main function
******************************************************************/
int main() {

    // name of the files based on the dataset
    string file1 = "huffmancoding_00000010_input.txt";
    string file2 = "huffmancoding_00000100_input.txt";
    string file3 = "huffmancoding_00001000_input.txt";
    string file4 = "huffmancoding_00010000_input.txt";
    string file5 = "huffmancoding_00100000_input.txt";

     generateRandomInput(file1, 10);
     generateRandomInput(file2, 100);
     generateRandomInput(file3, 1000);
     generateRandomInput(file4, 10000);
     generateRandomInput(file5, 100000);
    return 0;
}
