//este ejemplo es de la tarea pero de forma mala.
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

using namespace std;

//clase grafo basado en una tabla de vertices a vecinos
class Graph {
public:

//unordered_map es una tabla hash, hay que ver como pasarle state a la tabla hash
                //llaves, vertices y vecinos
    unordered_map <int, set<int>> vecinos;
                    //color
    unordered_map <int, int> colores;

    Graph(){
    }
    /*

    aristas es un vector de vectores de dos elementos,
    representa una arista entre los dos vertices
    ejemplo: {{0,1},{1,2},{2,3},{3,0}}
    */

   Graph(vector<vector<int>> aristas){
    for(auto arista: aristas){
        int u = arista[0];
        int v = arista[1];
        vecinos[u].insert(v);
        colores[u] = -1;
        vecinos[v].insert(u);
        colores[v] = -1;
    }
   }

   void print(){

        // Par es una estructura especial que contiene un par de elementos
        // donde par.first es el primero 
        // y par.second es el segundo

       for(auto par: vecinos){
           int u = par.first;           // vertice (llave)
           cout << u << ": ";
           for(auto v: par.second){     // v son todos los vecinos de u
               cout << v << ", ";
           }
           cout << endl;
       }

       cout << "Colores: " << endl;
         for(auto par: colores){
              cout << par.first << ": " << par.second<< endl;
        
        } 
   }

//branch and bound

    void greedyColoring(){
        set<int> colores_usados;

        for(auto par: vecinos){
            int u = par.first; //vertice llave
            set<int> vertices_vecinos = par.second; //vecinos de u

            // revisar en que colores en colores usados se
            // pueden utilizar

            for (auto c: colores_usados){
                
                set<int> color_vecinos;

                for(auto v : vertices_vecinos){

                    if(colores[v] != -1){
                        color_vecinos.insert(colores[v]);
                    }
                }

                if(color_vecinos.find(c) == color_vecinos.end()){
                    colores[u] = c;
                }

                    

                    
            }
            if (colores[u] == -1) { //caso no asignado

                if(colores_usados.size() == 0){
                    colores_usados.insert(0);
                } else {
                    int max = *(colores_usados.rbegin());
                    colores_usados.insert(max + 1);
                }
                colores[u] = *(colores_usados.rbegin());
            }
        }
    }
};

int main(){
    vector<vector<int>> aristas = {{0,1},
                                   {1,2},
                                   {2,3},
                                   {3,0}};
    Graph g(aristas);
    g.greedyColoring();
    g.print();
    return 0;

};