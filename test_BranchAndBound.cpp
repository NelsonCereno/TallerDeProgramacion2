#include "BranchAndBound.h"
#include "Graph.h"
#include "State.h"
#include <iostream>
#include <cassert>

void testBranchAndBound() {
    // Crear un grafo con algunas aristas
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    Graph graph(edges);
    State state(graph);
    BranchAndBound bb;

    // Verificar la función calculateLowerBound
    cout << "Verificando calculateLowerBound..." << endl;
    int lb = bb.calculateLowerBound(&state);
    assert(lb == 1);
    cout << "calculateLowerBound verificado correctamente." << endl;

    // Verificar la función selectVertex
    cout << "Verificando selectVertex..." << endl;
    int vertex = bb.selectVertex(&state);
    assert(vertex == 0);
    cout << "selectVertex verificado correctamente." << endl;

    // Verificar la función branchAndBound
    cout << "Verificando branchAndBound..." << endl;
    int numColors = bb.branchAndBound(&state);
    assert(numColors == 2);
    cout << "Resultado de branchAndBound: " << numColors << " colores" << endl;
    bb.best->printColor();
    cout << "branchAndBound verificado correctamente." << endl;

    cout << "Todas las pruebas de BranchAndBound pasaron." << endl;
}

int main() {
    testBranchAndBound();
    return 0;
}