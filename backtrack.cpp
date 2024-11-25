#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Graph {
    public:
    unordered_map<int, set<int>> vertexNeighbors; // vertex -> neighbors
    unordered_map<int, int> vertexColor; // vertex -> color
    Graph() {
    }
    // ya que se va a leer de un archivo de texto que
    // dos columnas con vertice - vertice
    Graph(vector<vector<int>> edges) {
        for (vector<int> edge : edges) {
            vertexNeighbors[edge[0]].insert(edge[1]);
            vertexNeighbors[edge[1]].insert(edge[0]);
        }
    }
    // OJO : esta funcion es cara hay que cambiarla
    int getNumberOfColors() {
        set<int> colors; // recordar que set almacena entero unicos, si se quiere almacena enteros no unicos utilizar multiset
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
    set<int> uncoloredVertices;
    set<int> coloredVertices;
    set<int> availableColors;
    Graph graph; // va a ser el grafo semi coloreado durante le desarrolo del algoritmo
    State() {
    }
    State(Graph graph) {
        this->graph = graph;
        // sacamos todos los vertices ya eue son llaves en el mapa
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

class ColoringOperation {
    public:
    State *best; // mejor estado encontrado
    ColoringOperation() {
        best = nullptr; // covenimos que nullptr es que no se ha encontrado ningun estado
    }
    int greedyColoring(State *s){
        while (!s->isAllColored()) {
            // seleccionamos un vertice y lo coloreamos
            int vertex = s->getVertex(); // necesitamos obtener un vértice no coloreado
            // encuentro el primer color disponible que sea factible (no igual al un color de vecinos)
            for (int color : s->availableColors) {
                if (s->graph.canColor(vertex, color)) {
                    s->pushColorSelectVertex(vertex, color);
                    break; // ya encontramos un color y actualizamos el estado
                }
            }
            // consulto si no se pudo colorear el vertice vertex
            if (!s->isVertexColored(vertex)) { // entonces debo colorearlo con un nuevo color
                int c = s->graph.getNumberOfColors();
                s->pushColorSelectVertex(vertex, c);
                s->availableColors.insert(c);
            }
            s->printColor();
        }
        best = s; // el mejor estado es el estado actual
        return s->graph.getNumberOfColors(); // retornamos el numero de colores
    }
    int backtrack(State *s) {
        // caso base
        if (s->isAllColored()) { // este estado es una hoja del algortimo
            if (best == nullptr || 
                s->graph.getNumberOfColors() < best->graph.getNumberOfColors()) {
                best = s;
            }
            return best->graph.getNumberOfColors();
        } else {    
            // caso recursivo
            int vertex = s->getVertex(); // se puede porque aun existen vertices sin colorear
            s->incrementColor(); // incrementamos el numero de colores
            for(int color : s->availableColors) {
                if (s->graph.canColor(vertex, color)) {
                    State *s1 = new State(*s);
                    s1->pushColorSelectVertex(vertex, color);

                    // if (condicion relativa a LB) si se cumple -> bactrack sino se salta  

                    backtrack(s1);
                }

            }
            return best->graph.getNumberOfColors();
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
    ColoringOperation co;
 //   co.greedyColoring(&s);
//    cout << "Numero de colores greedy: " << s.graph.getNumberOfColors() << endl;
 //   cout << "Mejor coloreo encontrado: ";
///    co.best->printColor();
    int c = co.backtrack(&s);
    cout << "Numero de colores backtrack : " << c << endl;
    co.best->printColor();
    return 0;
}