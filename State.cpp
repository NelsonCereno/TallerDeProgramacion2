#include "State.h"
#include <iostream>

using namespace std;

State::State() {
}

State::State(Graph graph) {
    this->graph = graph;
    // sacamos todos los vertices ya que son llaves en el mapa
    for (auto const& par : graph.vertexNeighbors) {
        uncoloredVertices.insert(par.first);
    }
}

int State::getVertex() {
    auto it = uncoloredVertices.begin();
    if (it == uncoloredVertices.end()) { // caso vacio
        return -1; // OJO: convenimos que si no hay mas entonces retornamos -1
    }
    return *it;
}

// sacamos el vertice no coloreados lo agregamos a los coloreados y lo coloreamos en graph
void State::pushColorSelectVertex(int vertex, int color) {
    graph.vertexColor[vertex] = color;
    coloredVertices.insert(vertex);
    uncoloredVertices.erase(vertex);
}

// consultamos si el vertice esta coloreado
bool State::isVertexColored(int vertex) {
    // find retorna un iterador, si el iterador es igual a end() entonces no se encontro
    return coloredVertices.find(vertex) != coloredVertices.end();
}

bool State::isAllColored() {
    return uncoloredVertices.size() == 0;
}

void State::printColor() {
    for (auto const& par : graph.vertexColor) {
        cout << par.first << "->" << par.second << " ";
    }
    cout << endl;
}

void State::incrementColor() {
    int c = graph.getNumberOfColors();
    availableColors.insert(c);
}