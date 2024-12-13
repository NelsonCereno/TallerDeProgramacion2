#include "State.h"
#include "Graph.h"
#include <iostream>
#include <cassert>

void testState() {
    // Crear un grafo con algunas aristas
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    Graph graph(edges);
    State state(graph);

    // Verificar que los vértices no coloreados se han cargado correctamente
    cout << "Verificando vértices no coloreados..." << endl;
    assert(state.uncoloredVertices.size() == 4);
    assert(state.coloredVertices.size() == 0);
    cout << "Vértices no coloreados verificados correctamente." << endl;

    // Imprimir el estado inicial
    cout << "Estado inicial:" << endl;
    state.printColor();

    // Verificar la función pushColorSelectVertex
    cout << "Verificando pushColorSelectVertex..." << endl;
    state.pushColorSelectVertex(0, 0);
    assert(state.isVertexColored(0) == true);
    assert(state.uncoloredVertices.size() == 3);
    assert(state.coloredVertices.size() == 1);
    cout << "Estado después de colorear el vértice 0:" << endl;
    state.printColor();
    cout << "pushColorSelectVertex verificado correctamente." << endl;

    // Verificar la función isAllColored
    cout << "Verificando isAllColored..." << endl;
    state.pushColorSelectVertex(1, 1);
    state.pushColorSelectVertex(2, 2);
    state.pushColorSelectVertex(3, 3);
    assert(state.isAllColored() == true);
    cout << "Estado después de colorear todos los vértices:" << endl;
    state.printColor();
    cout << "isAllColored verificado correctamente." << endl;

    cout << "Todas las pruebas de State pasaron." << endl;
}

int main() {
    testState();
    return 0;
}