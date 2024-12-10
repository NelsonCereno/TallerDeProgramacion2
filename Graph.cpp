#include "Graph.h"
#include <iostream>
#include <set>

using namespace std;

Graph::Graph() {
}

// ya que se va a leer de un archivo de texto que
// dos columnas con vertice - vertice
Graph::Graph(vector<vector<int>> edges) {
    for (vector<int> edge : edges) {
        vertexNeighbors[edge[0]].insert(edge[1]);
        vertexNeighbors[edge[1]].insert(edge[0]);
    }
}

// OJO : esta funcion es cara hay que cambiarla
int Graph::getNumberOfColors() {
    set<int> colors; // recordar que set almacena entero unicos, si se quiere almacena enteros no unicos utilizar multiset
    for (auto par : vertexColor) {
        colors.insert(par.second);
    }
    return colors.size();
}

// OJO: esta funcion es cara hay que cambiarla
// consulta si el vertice se puede colorear con el color dado
bool Graph::canColor(int vertex, int color) {
    for (int neighbor : vertexNeighbors[vertex]) {
        if (vertexColor.find(neighbor) != vertexColor.end() && 
            vertexColor[neighbor] == color) {
            // si es que se encontro el vecino en la lista de coloreados y tiene el color correcto
            return false;
        }
    }
    return true;
}

void Graph::printGraph() {
    for (auto const& par : vertexNeighbors) {
        cout << par.first << ": ";
        for (int neighbor : par.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}