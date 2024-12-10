#ifndef STATE_H
#define STATE_H

#include "Graph.h"
#include <set>

class State {
public:
    set<int> uncoloredVertices;
    set<int> coloredVertices;
    set<int> availableColors;
    Graph graph;
    State();
    State(Graph graph);
    int getVertex();
    void pushColorSelectVertex(int vertex, int color);
    bool isVertexColored(int vertex);
    bool isAllColored();
    void printColor();
    void incrementColor();
};

#endif // STATE_H