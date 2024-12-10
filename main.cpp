#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "Graph.h"
#include "State.h"
#include "BranchAndBound.h"

using namespace std;
using namespace std::chrono;

vector<vector<int>> readEdgesFromFile(const string& filename) {
    vector<vector<int>> edges;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    int u, v;
    while (file >> u >> v) {
        edges.push_back({u, v});
    }

    file.close();
    return edges;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    vector<vector<int>> edges = readEdgesFromFile(filename);

    Graph graph(edges);
    graph.printGraph();
    State s(graph);
    s.printColor();
    BranchAndBound bb;

    // Medir el tiempo de ejecución de branchAndBound
    auto start = high_resolution_clock::now();
    int c = bb.branchAndBound(&s);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Numero de colores branch and bound : " << c << endl;
    bb.best->printColor();
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    return 0;
}