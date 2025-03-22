
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*****************************************************************
This function is to generate the random input file
The random seed number is the group leader student id:
Muhammad Nafis Zahran (1201201241)
******************************************************************/
void generateRandomInput(string outputFile, int vertices) {

    // to create and write an output file
    ofstream outfile;
    outfile.open(outputFile);

    // to set a fixed seed value & generate the same sequence of random number
    srand(1201201241); // Nafis's student ID (Group leader)

    // Create a 2D vector (adjacencyMatrix) to store adjacency matrix
    vector<vector<int>> adjacencyMatrix(vertices, vector<int>(vertices, 0)); // set the initial index= 0

    outfile << vertices << endl;  // num of vertices
    for (int i = 0; i < vertices; i++){
        outfile << i << " " << 'V' << i << endl;  // vertex indexes and vertex names 0 V0
        }

    // adjacency matrix graph
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j) { //to ensure there is no self-loops
                adjacencyMatrix[i][j] = 0; // two diff vertices
            }
            else {
                int weight = rand() % 101; // (limit it to 0-100)
                adjacencyMatrix[i][j] = weight;
                adjacencyMatrix[j][i] = weight; // since it's an undirected graph
            }
        }
    }

    // To write matrix element in the file
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            // if weight = 0 (no edge), change with infinity (i)
            if (adjacencyMatrix[i][j] == 0) {
                outfile << "i"<< " ";
            }
            else
                outfile << adjacencyMatrix[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

/*****************************************************************
Main function
******************************************************************/
int main() {

    // name of the files based on the dataset
    string file1 = "kruskalwithoutpq_kruskalwithpq_am_00000010_input.txt";
    string file2 = "kruskalwithoutpq_kruskalwithpq_am_00000100_input.txt";
    string file3 = "kruskalwithoutpq_kruskalwithpq_am_00001000_input.txt";
    string file4 = "kruskalwithoutpq_kruskalwithpq_am_00010000_input.txt";
    string file5 = "kruskalwithoutpq_kruskalwithpq_am_00100000_input.txt";
    string file6 = "kruskalwithoutpq_kruskalwithpq_am_00005000_input.txt";


     generateRandomInput(file1, 10);
    // generateRandomInput(file2, 100);
    // generateRandomInput(file3, 1000);
    // generateRandomInput(file4, 10000);
    // generateRandomInput(file5, 100000);

    return 0;
}