#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
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

void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Cargar grafo" << endl;
    cout << "2. Mostrar grafo" << endl;
    cout << "3. Ejecutar Branch and Bound" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opción: ";
}

int main() {
    Graph graph;
    State s;
    BranchAndBound bb;
    string filename;
    vector<vector<int>> edges;
    int option;

    while (true) {
        displayMenu();
        cin >> option;

        switch (option) {
            case 1:
                cout << "Ingrese el nombre del archivo: ";
                cin >> filename;
                edges = readEdgesFromFile(filename);
                graph = Graph(edges);
                s = State(graph);
                bb = BranchAndBound(); // Reiniciar el estado de BranchAndBound
                cout << "Grafo cargado exitosamente." << endl;
                break;
            case 2:
                if (edges.empty()) {
                    cout << "Primero debe cargar un grafo." << endl;
                } else {
                    graph.printGraph();
                }
                break;
            case 3:
                if (edges.empty()) {
                    cout << "Primero debe cargar un grafo." << endl;
                } else {
                    auto start = high_resolution_clock::now();
                    int c = bb.branchAndBound(&s);
                    auto stop = high_resolution_clock::now();
                    duration<double> execDuration = duration_cast<duration<double>>(stop - start);

                    bb.best->printColor();
                    cout << "Numero de colores branch and bound : " << c << endl;
                    cout << fixed << setprecision(10);
                    cout << "Tiempo de ejecución: " << execDuration.count() << " segundos" << endl;
                }
                break;
            case 4:
                cout << "Saliendo..." << endl;
                return 0;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    }

    return 0;
}