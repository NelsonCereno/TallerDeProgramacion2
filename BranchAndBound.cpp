#include "BranchAndBound.h"
#include <climits>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

BranchAndBound::BranchAndBound() {
    best = nullptr;
    lowerBound = INT_MAX;
}

int BranchAndBound::calculateLowerBound(State *s) {

    int numColors = s->graph.getNumberOfColors();

    int maxSaturation = 0;
    for (int vertex : s->uncoloredVertices) {
        set<int> neighborColors;
        for (int neighbor : s->graph.vertexNeighbors[vertex]) {
            if (s->graph.vertexColor.find(neighbor) != s->graph.vertexColor.end()) {
                neighborColors.insert(s->graph.vertexColor[neighbor]);
            }
        }
        maxSaturation = max(maxSaturation, (int)neighborColors.size());
    }
    return max(numColors, maxSaturation + 1);
}

int BranchAndBound::selectVertex(State *s) {
    int selectedVertex = -1;
    int maxSaturation = -1;
    for (int vertex : s->uncoloredVertices) {
        if (s->isVertexColored(vertex)) {
            continue; // Saltar vértices ya coloreados
        }
        set<int> neighborColors;
        for (int neighbor : s->graph.vertexNeighbors[vertex]) {
            if (s->graph.vertexColor.find(neighbor) != s->graph.vertexColor.end()) {
                neighborColors.insert(s->graph.vertexColor[neighbor]);
            }
        }
        int saturation = neighborColors.size();
        if (saturation > maxSaturation) {
            maxSaturation = saturation;
            selectedVertex = vertex;
        }
    }
    return selectedVertex;
}

unordered_map<string, int> memo;

string stateToString(State *s) {
    // Convertir el estado a una cadena única para usar en memoización
    string stateStr;
    for (int vertex : s->uncoloredVertices) {
        stateStr += to_string(vertex) + ",";
    }
    return stateStr;
}

int BranchAndBound::branchAndBound(State *s) {
    string stateStr = stateToString(s);
    if (memo.find(stateStr) != memo.end()) {
        return memo[stateStr];
    }

    int lb = calculateLowerBound(s);
    if (lb >= lowerBound) {
        return lowerBound;
    }

    if (s->isAllColored()) {
        if (best == nullptr || s->graph.getNumberOfColors() < best->graph.getNumberOfColors()) {
            best = new State(*s); // Crear una copia del mejor estado
            lowerBound = s->graph.getNumberOfColors();
        }
        return best->graph.getNumberOfColors();
    } else {
        int vertex = selectVertex(s);
        if (vertex == -1) {
            return lowerBound; // No hay vértices sin colorear
        }
        s->incrementColor();
        for (int color : s->availableColors) {
            if (s->graph.canColor(vertex, color)) {
                State *s1 = new State(*s);
                s1->pushColorSelectVertex(vertex, color);
                branchAndBound(s1);
                delete s1;
            }
        }
        memo[stateStr] = lowerBound;
        return lowerBound;
    }
}
