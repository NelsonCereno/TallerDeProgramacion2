#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int id;
    int color;
    Node() {
        this->id = -1;
        this->color = -1;
    }   
    Node(int id, int color) {
        this->id = id;
        this->color = color;
    }
    /* OJO:debemos crear el operador == para que el unordered_map pueda comparar los nodos (obligatorio)
       esto para el caso que utilicen un objeto y no el puntero
    este & significa que trae el ambiente donde esta definido n en la llamada

    */
    bool operator==(const Node& other) const {
        return id == other.id && color == other.color;
    }
};

/*
necesitamos una funcion hash para los nodos
que es lo que va a generar la llave en el unordered_map
*/
struct NodeHash {
    // notar que no se puso el & en el argumento de la funcion
    // esto es porque se esta utilizando el operador de referencia *
    // basta con los const
    size_t operator()(const Node* n) const {
        return hash<int>()(n->id) ^ (hash<int>()(n->color) << 1); // esto es una funcion hash, se utiliza el operador XOR y un shift
        // la funcion hash<int>()(n->id) es una funcion hash que viene por defecto en c++ templatizada para varios tipos de datos incluyendo vectores
    }
};

/*
necesitamos una funcion de comparacion de igualdad para los nodos
que es lo que va a comparar los nodos en el unordered_map
*/
struct NodeEqual {
    bool operator()(const Node* n1, const Node* n2) const {
        return n1->id == n2->id && n1->color == n2->color;
    }
};

int main() {
    // esta es la tabla de hash con la funcion de hash
    // primer tipo es la llave, notar que es un puntero a nodo por lo que debemos definir la funcion de hash
    // el segundo tipo es el valor
    // el tercer tipo es la funcion de hash, que definimos mas arriba
    unordered_map<Node*, int, NodeHash, NodeEqual> n;
    Node* n1 = new Node(1, 2);
    Node* n2 = new Node(2, 3);
    // diferentes formas de insertar un valor
    n[n1] = 10;
    n[n2] = 20;
    n[new Node(3, 4)] = 30;
    n.insert({new Node(4, 5), 40}); // aqui insertamos un par de valores
    n.insert({new Node(5, 6), 50});
    
    // iteramos sobre la tabla de hash  
    for(auto it = n.begin(); it != n.end(); it++) {
        cout << "id:" << it->first->id << " color:" << it->first->color << " value:" << it->second << endl;
    }

    // buscamos un valor si es que esta en la tabla de hash
    Node* n3 = new Node(1, 2);
    if(n.find(n3) != n.end()) {
        cout << "id:" << n3->id << " color:" << n3->color << " value:" << n[n3] << " FOUND!" << endl;
    } else {
        cout << "no se encontro el valor" << endl;
    }

    // borramos los nodos
    for(auto it = n.begin(); it != n.end(); it++) {
        delete it->first;
    }
    delete n3;

    // Podemos tener nodos de llave y valor. Pongamos este caso no puntero

    struct NodeHash2 {
        size_t operator()(const Node& n) const {
            return hash<int>()(n.id) ^ (hash<int>()(n.color) << 1);
        }
    };

    struct NodeEqual2 {
        bool operator()(const Node& n1, const Node& n2) const {
            return n1.id == n2.id && n1.color == n2.color;
        }
    };
    
    unordered_map<Node, Node, NodeHash2, NodeEqual2> nn2;
    nn2[Node(1, 2)] = Node(2, 3);
    nn2[Node(2, 3)] = Node(3, 4);
    nn2[Node(3, 4)] = Node(4, 5);
    nn2[Node(4, 5)] = Node(5, 6);
    nn2[Node(5, 6)] = Node(6, 7);

    for(auto it = nn2.begin(); it != nn2.end(); it++) {
        cout << "id:" << it->first.id << " color:" << it->first.color << " value id:" << it->second.id << " value color:" << it->second.color << endl;
    }

    return 0;
}