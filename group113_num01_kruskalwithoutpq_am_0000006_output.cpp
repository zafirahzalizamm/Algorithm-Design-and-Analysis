#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include <fstream>
#include <ctime>

using namespace std;

// Class Edge, used to store all edges
class Edge
{
    string v1;
    string v2;
    int value;

public:
    void setV1(string tempV1)
    {
        v1 = tempV1;
    }

    void setV2(string tempV2)
    {
        v2 = tempV2;
    }

    void setValue(int tempValue)
    {
        value = tempValue;
    }

    string getV1()
    {
        return v1;
    }

    string getV2()
    {
        return v2;
    }

    int getValue()
    {
        return value;
    }
};


// Global Variables //
static int numOfVertices = 0;                   // number of vertices
static int numOfEdges = 0;                      // number of edges
static int totalWeightMST = 0;                  // total weight of selected edges for MST

static vector<string> vectVertices;             // list of the name of vertices
static vector<Edge> vectEdge;                   // list of all available edges
static vector<Edge> vectMST;                    // list of selected edge for MST
static vector< vector<int> > vectAdjMatrix;     // Store adjacency matrix (used in #3)

clock_t startTime;                              // record initial time
clock_t endTime;                                // record end time
double duration;                                // store time taken for the algorithm to complete execution


// Function to get input from file
void inputData()
{
    int tempNumOfVertices;

    ifstream inFile;
    inFile.open("kruskalwithoutpq_kruskalwithpq_am_00000006_input.txt");

    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }


    inFile >> tempNumOfVertices;
    numOfVertices = tempNumOfVertices;

    for (int i = 0; i < numOfVertices; i++)
    {
        vectVertices.push_back(" ");
    }

    // #2: Input number of vertices

    int tempIndexV;     // Store index of vertices
    string tempNameV;   // Store names of vertices

    for (int i = 0; i < numOfVertices; i++)
    {
        inFile >> tempIndexV;
        inFile >> tempNameV;

        vectVertices[tempIndexV] = tempNameV;
    }


    // #3: Input adjacency matrix

    char strData;
    int intData;
    vectAdjMatrix.resize(numOfVertices);     // Store adjacency matrix

    vector<string> words;
    stringstream ss(" ");
    string word;
    string tempLine;

    inFile.ignore();


    // #3.1: Get data from 2D matrix from input file

    // get all value from rows and columns from input file
    // store everything in a vector of string
    for (int i = 0; i < numOfVertices; i++)
    {
        ss.clear();
        getline(inFile, tempLine);

        // string stream
        ss << tempLine;

        // split and append in vector words
        while (ss >> word)
        {
            words.push_back(word);
        }

    }

    int tempAscii;
    string tempStr = "";

    int tempNum = 0;            // store temporary Ascii value of weight
    int tempTotalNum = 0;       // store the value of weight from Ascii value
    int tempTotalEdge = 0;      // store total edge inserted


    // #3.2: Validate data previous input vector
    //       Determine weight and push into 2D vector matrix

    // loop through vector<string> words
    // get the value and place in the correct row and column index
    for (int i = 0; i < numOfVertices; i++)
    {

        for (int j = i * numOfVertices; j < (numOfVertices + (i * numOfVertices)); j++)
        {

            tempStr = words[j];
            tempAscii = (int)tempStr[0];

            // if the first letter of the weight is not a num
            // = the weight is not a num / invalid weight
            if (tempAscii < 48 || tempAscii > 57)
            {
                vectAdjMatrix[i].push_back(0);
            }
            // if the first letter of the weight is a num
            // = the weight is valid
            else
            {
                tempNum = 0;
                tempTotalNum = 0;

                // convert string to Ascii
                // convert Ascii to int with the correct value as in previous string format
                for (int k = 0; k < tempStr.size(); k++)
                {
                    tempNum = (int)tempStr[k];
                    tempTotalNum += (tempNum - 48) * pow(10,tempStr.size() - 1 - k);
                }

                vectAdjMatrix[i].push_back(tempTotalNum);
                tempTotalEdge += 1;
            }
        }
    }

    numOfEdges = tempTotalEdge / 2;
}


// Function to insert the data from the adjacency matrix
// into the object vector<Edge> vectEdge
void insertIntoVectEdge()
{
    string currentRowName = "";
    string currentColName = "";
    Edge tempEdge;
    int tempAsciiV1 = 0;
    int tempAsciiV2 = 0;

    // loop to access only the upper triangle of the adjacency matrix
    for (int i = 0; i < vectAdjMatrix.size(); i++)
    {
        for (int j = i + 1; j < vectAdjMatrix.size(); j++)
        {

            currentRowName = vectVertices[i];
            currentColName = vectVertices[j];

            if (vectAdjMatrix[i][j] != 0)
            {
                // check the Ascii value of vertices
                int tempIndex = 0;
                do
                {
                    tempAsciiV1 = (int)currentRowName[tempIndex];
                    tempAsciiV2 = (int)currentColName[tempIndex];
                    tempIndex += 1;
                }
                while (tempAsciiV1 == tempAsciiV2);

                // select the vertex with lower Ascii value as v1
                if (tempAsciiV1 < tempAsciiV2 || tempAsciiV1 == tempAsciiV2)
                {
                    tempEdge.setV1(currentRowName);
                    tempEdge.setV2(currentColName);
                }
                else
                {
                    tempEdge.setV1(currentColName);
                    tempEdge.setV2(currentRowName);
                }

                // set the weight value of the edge
                tempEdge.setValue(vectAdjMatrix[i][j]);

                // insert into vector<Edge> vectEdge
                vectEdge.push_back(tempEdge);
            }
        }
    }
}


// Function to select the edge with the smallest weight value
Edge selectSmallestEdge()
{
    // set the value of the first element in vectEdge as the smallest edge
    Edge smallestEdge = vectEdge[0];
    Edge tempEdge;
    int largestLength = 0;

    int tempAsciiV1 = 0;
    int tempAsciiV2 = 0;
    int tempIndex = 0;

    // loop through vectEdge
    for (int i = 1; i < vectEdge.size(); i++)
    {
        // compare the weight value with the next element in vector
        if (vectEdge[i].getValue() < smallestEdge.getValue())
        {
            smallestEdge = vectEdge[i];
        }
        else if (vectEdge[i].getValue() == smallestEdge.getValue())
        {
            // compare the Ascii value of the current smallest edgee
            // with the another element in the vector
            int tempIndex = 0;
            do
            {
                tempAsciiV1 = (int)smallestEdge.getV1()[tempIndex];
                tempAsciiV2 = (int)vectEdge[i].getV1()[tempIndex];
                tempIndex += 1;
            }
            while (tempAsciiV1 == tempAsciiV2);

            // select the edge with smallest weight and smallest Ascii value
            // as the smallest edge
            if (tempAsciiV2 < tempAsciiV1)
            {
                smallestEdge = vectEdge[i];
            }
        }
    }

    return smallestEdge;
}


// Function to search for the MST
// using Kruskal Algorithm
// and loop checking to avoid loop
void kruskalAlgorithmWithoutPriorityQueue()
{

    int tempIndex = -1;
    vector<int> vectCheckedEdgeIndex;
    string currentVertex = "";
    string originVertex = "";
    bool loopConfirmed = false;
    bool indexChecked = false;

    int counterMST = 0;
    int counterStack = 0;
    vector<int>::iterator it;
    vector<Edge>::iterator ie;
    vector<string>::iterator is;

    vector<string> stackVertices;   // store all vertices that can cause loop

    Edge smallestEdge;              // store current smallest edge

    // loop to select only specific number of edges for the MST
    while(vectMST.size() != numOfVertices - 1)
    {
        int i = 0;

        // find the smallest edge using the function selectSmallestEdge()
        smallestEdge = selectSmallestEdge();

        // insert into the vector<Edge> vectMST
        vectMST.push_back(smallestEdge);

        // first edge inserted
        if (vectMST.size() == 1)
        {
            // remove the corresponding edge from the vectEdge
            for (int k = 0; k < vectEdge.size(); k++)
            {
                if (vectEdge[i].getV1() == smallestEdge.getV1())
                {
                    if (vectEdge[i].getV2() == smallestEdge.getV2())
                    {
                        vectEdge.erase(vectEdge.begin() + k);

                    }
                }
            }
        }
        // if there is already any edge in the vectMST
        else
        {
            originVertex = smallestEdge.getV1();
            currentVertex = smallestEdge.getV2();
            tempIndex = i;
            counterMST = 0;
            counterStack = 1;

            vectCheckedEdgeIndex.clear();
            stackVertices.clear();

            stackVertices.push_back(smallestEdge.getV1());
            stackVertices.push_back(smallestEdge.getV2());

            // loop through stack
            while(counterStack < stackVertices.size())
            {
                // loop through vector of MST
                for (int j = 0; j < vectMST.size() - 1; j++)
                {
                    if (stackVertices[counterStack] == vectMST[j].getV1())
                    {
                        // loop confirmed
                        if (vectMST[j].getV2() == originVertex)
                        {
                            // remove the newly added edge since there is a loop
                            vectMST.pop_back();
                            loopConfirmed = true;
                            break;
                        }

                        // check if the vertex is in stack
                        is = find(stackVertices.begin(), stackVertices.end(), vectMST[j].getV2());

                        // the vertex is already in stack
                        if (is != stackVertices.end())
                        {
                            // do nothing
                        }

                        // the vertex is not in stack
                        else
                        {
                            // insert the vertex into stack
                            stackVertices.push_back(vectMST[j].getV2());
                        }
                    }

                    else if (stackVertices[counterStack] == vectMST[j].getV2())
                    {

                        // loop confirmed
                        if (vectMST[j].getV1() == originVertex)
                        {
                            // remove the newly added edge since there is a loop
                            vectMST.pop_back();
                            loopConfirmed = true;
                            break;
                        }

                        // check if the vertex is in stack
                        is = find(stackVertices.begin(), stackVertices.end(), vectMST[j].getV1());

                        // the vertex is already in stack
                        if (is != stackVertices.end())
                        {
                            // do nothing
                        }

                        // the vertex is not in stack
                        else
                        {
                            // insert the vertex into stack
                            stackVertices.push_back(vectMST[j].getV1());
                        }
                    }
                }

                counterStack += 1;
            }

            // remove selected edge from vectEdge
            for (int k = 0; k < vectEdge.size(); k++)
            {
                if (vectEdge[k].getV1() == smallestEdge.getV1())
                {
                    if (vectEdge[k].getV2() == smallestEdge.getV2())
                    {
                        vectEdge.erase(vectEdge.begin() + k);

                    }
                }
            }
        }
    }

    // calculate total weight of MST
    for (int i = 0; i < vectMST.size(); i++)
    {
        totalWeightMST += vectMST[i].getValue();
    }
}


// Function to display output of screen
void displayOutput()
{
    // write number of vertices
    cout << numOfVertices << endl;

    // write all vertices' indexes and names
    for (int i = 0; i < vectVertices.size(); i++)
    {
        cout << i << " " << vectVertices[i] << endl;
    }

    // write all edges in MST
    for (int j = 0; j < vectMST.size(); j++)
    {
        cout << vectMST[j].getV1() << " " << vectMST[j].getV2() << " " << vectMST[j].getValue() << endl;
    }

    // write total weight of MST
    cout << totalWeightMST << endl;

    // write total time taken
    clock_t endTime = clock();
    duration = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    cout << duration << "s" << endl;
}


// Function to write output into a txt file
void outputData()
{
    // object to open file
    ofstream outFile;
    outFile.open("group113_num01_kruskalwithoutpq_am_00000006_outputs.txt");

    if(!outFile)   // file couldn't be opened
    {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    // write number of vertices
    outFile << numOfVertices << endl;

    // write all vertices' indexes and names
    for (int i = 0; i < vectVertices.size(); i++)
    {
        outFile << i << " " << vectVertices[i] << endl;
    }

    // write all edges in MST
    for (int j = 0; j < vectMST.size(); j++)
    {
        outFile << vectMST[j].getV1() << " " << vectMST[j].getV2() << " " << vectMST[j].getValue() << endl;
    }

    // write total weight of MST
    outFile << totalWeightMST << endl;

    // write total time taken
    outFile << duration << "s" << endl;

}


// Main function
int main()
{
    // Record initial time
    startTime = clock();

    // Algorithm

    // Read data from a txt file
    inputData();

    // Store data for computation
    insertIntoVectEdge();

    // Search and calculate the MST
    kruskalAlgorithmWithoutPriorityQueue();

    // Display output onto screen
    displayOutput();

    // Write output into a txt file
    // Record end time and calculate duration
    outputData();

    return 0;
}

