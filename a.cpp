#include "BranchAndBound.h"
#include <climits>
#include <algorithm>

using namespace std;

BranchAndBound::BranchAndBound() {
    best = nullptr;
    lowerBound = INT_MAX;
}

int BranchAndBound::calculateLowerBound(State *s) {
    // Heurística 1: Número de colores actuales
    int numColors = s->graph.getNumberOfColors();

    // Heurística 2: Grado de saturación (DSatur)
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

    // Combinamos las heurísticas para calcular la cota inferior
    return max(numColors, maxSaturation + 1);
}

int BranchAndBound::selectVertex(State *s) {
    // Seleccionamos el vértice con el mayor grado de saturación (DSatur)
    int selectedVertex = -1;
    int maxSaturation = -1;
    for (int vertex : s->uncoloredVertices) {
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

int BranchAndBound::branchAndBound(State *s) {
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

                // Liberar memoria del objeto State creado dinámicamente
                delete s1;
            }
        }
        return lowerBound;
    }
}