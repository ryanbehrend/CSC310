#include "splay.h"
#include <chrono>
#include <fstream>
#include <string>

using namespace std;
using namespace chrono;

int main()
{
    string file = "accessPattern/accessPattern/sequential.txt";
    //string file = "accessPattern/accessPattern/uniform_random.txt";
    //string file = "accessPattern/accessPattern/working_set.txt";
    //string file = "accessPattern/accessPattern/zipf_skewed.txt";

    SplayTree tree;

    // Create the tree
    ifstream inputFileFirst(file);
    if (!inputFileFirst.is_open())
    {
        cout << "Error: file did not open" << endl;
        return 0;
    }

    string line;
    while (getline(inputFileFirst, line))
    {
        int val = stoi(line);
        tree.insert(val);
    }

    inputFileFirst.close();

    // Search the created tree
    ifstream inputFileSecond(file);
    if (!inputFileSecond.is_open())
    {
        cout << "Error: file did not open" << endl;
        return 0;
    }

    auto startTime = high_resolution_clock::now();

    while (getline(inputFileSecond, line))
    {
        int val = stoi(line);
        tree.search(val);
    }
    inputFileSecond.close();

    auto endTime = high_resolution_clock::now();

    // Calculate and print results
    auto totalTime = duration_cast<milliseconds>(endTime - startTime).count();

    double avgDepth;
    if (tree.searchCount == 0)
    {
        avgDepth = 0.0;
    }
    else
    {
        avgDepth = static_cast<double>(tree.totalSearchDepth) / tree.searchCount;
    }

    cout << "Total Rotation Count: " << tree.rotationCount << endl;
    cout << "Average search depth: " << avgDepth << endl;
    cout << "Total time in milliseconds: " << totalTime << endl;

    return 0;
}
