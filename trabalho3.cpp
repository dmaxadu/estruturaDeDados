/* 
 * Programa: topologicalSort.cpp;
 * Autor: Daniel Machado;
 * DRE: 121046088;
 * Descrição: Ordenação topológica de um grafo;
 */

#include <iostream>
#include <list>

#define ERROR cout << "Error!\nTry again!" << endl; return 0;

using namespace std;

//stack class

const int maxItems = 100;

class Stack{
    private:
    int top;
    int size;
    int* structure;

    public:
    Stack();
    ~Stack();
    bool full();
    bool empty();
    int push(int item);
    int pop();
    int peek();
    void print();

};

Stack::Stack(){
    size = 0;
    top = 0;
    structure = new int[maxItems];
}

Stack::~Stack(){
    delete [] structure;
}

bool Stack::full(){
    if(size == maxItems){
        return true;
    }
    return false;
}

bool Stack::empty(){
    if(size == 0){
        return true;
    }
    else{
        return false;
    }
}

int Stack::push(int item){
    if(!full()){
        structure[size] = item;
        size++;
    }
    else{
        cout << "Erro no push";
        ERROR;
    }

    return 0;
};

int Stack::pop(){
    if(empty()){
        cout << "Erro no pop";
        ERROR;
    
    }
    else{
        size--;
        return structure[size];
    }
    return 0;
}

int Stack::peek(){
    if(empty()){
        cout << "Erro no peek";
        ERROR;
        exit(EXIT_FAILURE);
    }
    else{
        return structure[size - 1];
    }
    return 0;
}

void Stack::print(){
    cout << "\n[ ";
    for(int i = 0; i < size; i++){
        cout << structure[i] << " ";
    }
    cout << "]\n";
}


//graph class

class Graph{
    int v;
    list<int>* adjacency;
    void topologicalSortAux(int v, bool visited[], Stack stack);

    public:
        Graph(int v);
        void addEdge(int v, int element);
        void topologicalSort();
};

Graph::Graph(int v){
    this->v = v;
    adjacency = new list<int>[v];
};

void Graph::addEdge(int v, int element){
    adjacency[v].push_back(element);
};

void Graph::topologicalSortAux(int v, bool visited[], Stack stack){
    visited[v] = true;
    list<int>::iterator i;
    for(i = adjacency[v].begin(); i != adjacency[v].end(); i++){
        if(!visited[*i]){
            topologicalSortAux(*i, visited, stack);
        };
    };
    stack.push(v);
};

void Graph::topologicalSort()
{
    Stack stack;
  
    bool* visited = new bool[v];
    for(int i = 0; i < v; i++){
        visited[i] = false;
    };

    for(int i = 0; i < v; i++){
        if(visited[i] == false){
            topologicalSortAux(i, visited, stack);
        };
    };
  
    while(stack.empty() == false){
        cout << stack.peek() << " ";
        stack.pop();
    };
};