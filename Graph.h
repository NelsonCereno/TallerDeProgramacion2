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
    unordered_map<int, set<int>> colorNeighbors; // vertex -> set of colors of neighbors
    int colorCount; // number of unique colors

    Graph();
    Graph(vector<vector<int>> edges);
    int getNumberOfColors();
    bool canColor(int vertex, int color);
    void setColor(int vertex, int color);
    void printGraph();
};

#endif // GRAPH_H