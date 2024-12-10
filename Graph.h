#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

class Graph {
public:
    unordered_map<int, set<int>> vertexNeighbors; // vertex -> neighbors
    unordered_map<int, int> vertexColor; // vertex -> color
    Graph();
    Graph(vector<vector<int>> edges);
    int getNumberOfColors();
    bool canColor(int vertex, int color);
    void printGraph();
};

#endif // GRAPH_H