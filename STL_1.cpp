#include <iostream>
using namespace std;

#include <vector>
#include <set>


int main(){

    struct tipo {
        int x;
        //llamado a operador sobrecargado
        int operator+(tipo a){
            return x + a.x;
        }
        //llamado a operador sobrecargado
        int operator()(int y){
            return y + x;
        }
        //llamado a operador sobrecargado
        int operator[](int y){
            return 2*y + x;
        }
    };

//Se le llama funtor porque la estructura se lee como una función
    tipo a, b;
    a.x = 5;
    b.x = 3;

    //Se llama a los operadores sobrecargados
    cout << a + b << endl;
    cout << a(10) << endl;
    cout << a[10] << endl;

    cout << "ejemplos de vector" << endl;
    //Se declaran vectores de enteros
    vector<int> A;

    //Se agregan elementos al vector
    A.push_back(10);
    A.push_back(1);
    A.push_back(5);
    A.push_back(3);

    //Se imprime el primer elemento del vector
    cout << A[0] << endl;
    cout << A[1] << endl;

    //Esta mal porque esta fuera de la memoria del vector
    //cout << A[10] << endl;


//Uso de fors

    //Mostrar un arreglo a la antigua
    for(int i = 0; i < A.size(); i++){
        cout << A[i] << " ";
    }
    cout << endl;

    //Mostrar arreglo a la nueva con ayuda de Auto
    //Auto detecta el tipo de dato de forma automatica

    for(auto i : A){
        cout << i << " ";
    }
    cout << endl;

//Ahora veamos con iteradores
    auto i = A.begin(); // i es un "puntero" al inicio de la estructura A

    //Probemos que se parece a un puntero
    cout << *i << endl;
    i++;
    cout << *i << endl;
    //Efectivamente hace como si fuera un puntero sin serlo realmente

    //Se recorre el vector con iteradores
    //Sirve para arboles 
    for(auto j = A.begin(); j != A.end(); j++){
        cout << *j << " ";
    }
    cout << endl;

//Se define un Set

    //arbol red-black de enteros sin repeticion
    set<int> z;
    z.insert(100);
    z.insert(1);
    z.insert(50);
    z.insert(2);
    z.insert(60);
    z.insert(10);

    //Se recorre el set
    //begin cuesta log
    //insert cuesta log
    for(auto w : z){
        cout << w << " ";
    }
    cout << endl;

    //Hace el recorrido de forma correcta con iteradores
    //con begin y w++
    for(auto w = z.begin(); w != z.end(); w++){
        cout << *w << " ";
    }
    cout << endl;

//Definamos la clase State
    cout << "\nDefinamos la clase State" << endl;
    class State{
        public:
            State(int x){
                this->x = x;
            }
            int x;
    };

//Se define un set de State
    set<State *> h;

//Se crean objetos de State
    State *s1 = new State(100);
    State *s2 = new State(1);
    State *s3 = new State(15);
    State *s4 = new State(6);

//Se insertan los objetos en el set
    h.insert(s1);
    h.insert(s2);
    h.insert(s3);
    h.insert(s4);

//Se ordenan los valores esta vez pero por direccion de memoria
    for (auto k: h){
        cout << k->x << " ";
    }
    cout << endl;

//Para solucionar esto creamos comparador
    struct Comparador{
        bool operator()(const State* s1, const State* s2) const {
            return s1->x < s2->x;
        }

    };

//Se define un set de State con comparador
    set<State*, Comparador> hh;

//Se insertan los objetos en el set

//hh.remove(hh.begin()) elimina el primer elemento
//hh.remove(hh.rbegin()) elimina el ultimo elemento
//hh.begin() puntero al primer elemento
//hh.rbegin() puntero al ultimo elemento

    hh.insert(s1);
    hh.insert(s2);
    hh.insert(s3);
    hh.insert(s4);

//Se ordenan los valores esta vez pero por direccion de memoria
    for (auto k: hh){
        cout << k->x << " ";
    }
    cout << endl;       
}

