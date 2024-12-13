#include "Graph.h"
#include <iostream>
#include <cassert>

void testGraph() {
    // Crear un grafo con algunas aristas
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    Graph graph(edges);

    // Verificar que los vecinos se han cargado correctamente
    cout << "Verificando vecinos..." << endl;
    assert(graph.vertexNeighbors[0].size() == 2);
    assert(graph.vertexNeighbors[1].size() == 2);
    assert(graph.vertexNeighbors[2].size() == 2);
    assert(graph.vertexNeighbors[3].size() == 2);
    cout << "Vecinos verificados correctamente." << endl;

    // Imprimir el grafo
    cout << "Contenido del grafo:" << endl;
    graph.printGraph();

    // Verificar la función canColor
    cout << "Verificando canColor..." << endl;
    graph.vertexColor[0] = 0; // Colorear vértice 0 con color 0
    graph.vertexColor[1] = 1; // Colorear vértice 1 con color 1
    cout << "Vértice 0 coloreado con color 0" << endl;
    cout << "Vértice 1 coloreado con color 1" << endl;

    // Verificar si el vértice 2 puede ser coloreado con diferentes colores
    if (graph.canColor(2, 0)) {
        cout << "El vértice 2 puede ser coloreado con color 0" << endl;
    } else {
        cout << "El vértice 2 NO puede ser coloreado con color 0" << endl;
    }
    if (graph.canColor(2, 1)) {
        cout << "El vértice 2 puede ser coloreado con color 1" << endl;
    } else {
        cout << "El vértice 2 NO puede ser coloreado con color 1" << endl;
    }
    if (graph.canColor(2, 2)) {
        cout << "El vértice 2 puede ser coloreado con color 2" << endl;
    } else {
        cout << "El vértice 2 NO puede ser coloreado con color 2" << endl;
    }

    // Verificar si el vértice 3 puede ser coloreado con diferentes colores
    if (graph.canColor(3, 0)) {
        cout << "El vértice 3 puede ser coloreado con color 0" << endl;
    } else {
        cout << "El vértice 3 NO puede ser coloreado con color 0" << endl;
    }
    if (graph.canColor(3, 1)) {
        cout << "El vértice 3 puede ser coloreado con color 1" << endl;
    } else {
        cout << "El vértice 3 NO puede ser coloreado con color 1" << endl;
    }
    if (graph.canColor(3, 2)) {
        cout << "El vértice 3 puede ser coloreado con color 2" << endl;
    } else {
        cout << "El vértice 3 NO puede ser coloreado con color 2" << endl;
    }
    cout << "canColor verificado correctamente." << endl;

    // Verificar la función getNumberOfColors
    cout << "Verificando getNumberOfColors..." << endl;
    graph.vertexColor[2] = 2; // Colorear vértice 2 con color 2
    int numColors = graph.getNumberOfColors();
    cout << "Número de colores utilizados: " << numColors << endl;
    cout << "Colores almacenados en el grafo:" << endl;
    for (const auto& pair : graph.vertexColor) {
        cout << "Vértice " << pair.first << " -> Color " << pair.second << endl;
    }
    assert(numColors == 3);
    cout << "getNumberOfColors verificado correctamente." << endl;

    cout << "Todas las pruebas de Graph pasaron." << endl;
}

int main() {
    testGraph();
    return 0;
}