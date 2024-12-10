/*
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <climits>

using namespace std;

class Graph {
    public:
    unordered_map<int, set<int>> vertexNeighbors; // vertex -> neighbors
    unordered_map<int, int>> vertexColor; // vertex -> color
    Graph() {
    }
    // ya que se va a leer de un archivo de texto que
    // dos columnas con vertice - vertice
    Graph(vector<vector<int>> edges) {
        for (vector<int>> edge : edges) {
            vertexNeighbors[edge[0]].insert(edge[1]);
            vertexNeighbors[edge[1]].insert(edge[0]);
        }
    }
    // OJO : esta funcion es cara hay que cambiarla
    int getNumberOfColors() {
        set<int>> colors; // recordar que set almacena entero unicos, si se quiere almacena enteros no unicos utilizar multiset
        for (auto par:vertexColor) {
            colors.insert(par.second);
        }
        return colors.size();
    }
    // OJO: esta funcion es cara hay que cambiarla
    // consulta si el vertice se puede colorear con el color dado
    bool canColor(int vertex, int color) {
        for (int neighbor : vertexNeighbors[vertex]) {
            if (vertexColor.find(neighbor) != vertexColor.end() && 
                vertexColor[neighbor] == color) {
                // si es que se encontro el vecino en la lista de coloreados y tiene el color correcto
                return false;
            }
        }
        return true;
    }
    void printGraph() {
        for (auto const& par : vertexNeighbors) {
            cout << par.first << ": ";
            for (int neighbor : par.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

// necesitamos una clase especial para el algoritmo de backtracking
// lista de vertices sin colorear, lista de vertices coloreados, lista de colores disponibles
class State {
    public:
    set<int>> uncoloredVertices;
    set<int>> coloredVertices;
    set<int>> availableColors;
    Graph graph; // va a ser el grafo semi coloreado durante le desarrolo del algoritmo
    State() {
    }
    State(Graph graph) {
        this->graph = graph;
        // sacamos todos los vertices ya que son llaves en el mapa
        for (auto const& par : graph.vertexNeighbors) {
            uncoloredVertices.insert(par.first);
        }
    }
    int getVertex(){
        auto it = uncoloredVertices.begin();
        if (it==uncoloredVertices.end()) { // caso vacio
            return -1; // OJO: convenimos que si no hay mas entonces retornamos -1
        }
        return *it;
    }
    // sacamos el vertice no coloreados lo agregamos a los coloreados y lo coloreamos en graph
    void pushColorSelectVertex(int vertex, int color) {
        graph.vertexColor[vertex] = color;
        coloredVertices.insert(vertex);
        uncoloredVertices.erase(vertex);
    }

    // consultamos si el vertice esta coloreado
    bool isVertexColored(int vertex) {
        // find retorna un iterador, si el iterador es igual a end() entonces no se encontro
        return coloredVertices.find(vertex) != coloredVertices.end();
    }

    bool isAllColored() {
        return uncoloredVertices.size() == 0;
    }

    void printColor() {
        for (auto const& par : graph.vertexColor) {
            cout << par.first << "->" << par.second << " ";
        }
        cout << endl;
    }

    void incrementColor() {
        int c = graph.getNumberOfColors();
        availableColors.insert(c);
    }

};

class BranchAndBound {
    public:
    State *best; // mejor estado encontrado
    int lowerBound; // cota inferior

    BranchAndBound() {
        best = nullptr; // convenimos que nullptr es que no se ha encontrado ningun estado
        lowerBound = INT_MAX; // inicializamos la cota inferior con el valor máximo posible
    }

    int calculateLowerBound(State *s) {
        // Heurística 1: Número de colores actuales
        int numColors = s->graph.getNumberOfColors();

        // Heurística 2: Número de vértices no coloreados
        int numUncoloredVertices = s->uncoloredVertices.size();

        // Heurística 3: Grado de saturación (DSatur)
        int maxSaturation = 0;
        for (int vertex : s->uncoloredVertices) {
            set<int>> neighborColors;
            for (int neighbor : s->graph.vertexNeighbors[vertex]) {
                if (s->graph.vertexColor.find(neighbor) != s->graph.vertexColor.end()) {
                    neighborColors.insert(s->graph.vertexColor[neighbor]);
                }
            }
            maxSaturation = max(maxSaturation, (int)neighborColors.size());
        }

        // Combinamos las heurísticas para calcular la cota inferior
        return max(numColors, maxSaturation + 1);
    }

    int selectVertex(State *s) {
        // Seleccionamos el vértice con el mayor grado de saturación (DSatur)
        int selectedVertex = -1;
        int maxSaturation = -1;
        for (int vertex : s->uncoloredVertices) {
            set<int>> neighborColors;
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

    int branchAndBound(State *s) {
        // Calculamos la cota inferior para el estado actual
        int lb = calculateLowerBound(s);

        // Si la cota inferior es mayor o igual a la mejor solución actual, podar la rama
        if (lb >= lowerBound) {
            return lowerBound;
        }

        // Caso base: si todos los vértices están coloreados
        if (s->isAllColored()) {
            if (best == nullptr || s->graph.getNumberOfColors() < best->graph.getNumberOfColors()) {
                best = s;
                lowerBound = s->graph.getNumberOfColors(); // Actualizamos la cota inferior
            }
            return best->graph.getNumberOfColors();
        } else {
            // Caso recursivo: seleccionamos un vértice y lo coloreamos
            int vertex = selectVertex(s); // Seleccionamos el vértice con mayor grado de saturación
            s->incrementColor(); // Incrementamos el número de colores
            for (int color : s->availableColors) {
                if (s->graph.canColor(vertex, color)) {
                    State *s1 = new State(*s);
                    s1->pushColorSelectVertex(vertex, color);

                    // Llamada recursiva al branchAndBound
                    branchAndBound(s1);
                }
            }
            return lowerBound;
        }
    }
};

int main() {
    vector<vector<int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 5}, {1, 6},
        {2, 3}, {2, 6}, {2, 7},
        {3, 4}, {3, 7}, {3, 8},
        {4, 8}, {4, 9},
        {5, 6}, {6, 7}, {7, 8}, {8, 9},
        {5, 10}, {6, 10}, {7, 11}, {8, 11},
        {10, 11}, {10, 12}, {11, 12} };
    Graph graph(edges);
    graph.printGraph();
    State s(graph);
    s.printColor();
    BranchAndBound bb;
 //   bb.greedyColoring(&s);
//    cout << "Numero de colores greedy: " << s.graph.getNumberOfColors() << endl;
 //   cout << "Mejor coloreo encontrado: ";
///    bb.best->printColor();
    int c = bb.branchAndBound(&s);
    cout << "Numero de colores branch and bound : " << c << endl;
    bb.best->printColor();
    return 0;
}
*/