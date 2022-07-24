/* 
 * Programa: KruskalAlgorithm.c;
 * Autor: Daniel Machado;
 * DRE: 121046088;
 * Descrição: Executa o algoritmo de kruskal com union_find por rank e compressão de caminhos.
 */

#include <iostream>

using namespace std;

class Edge {
    public:
        int v1, v2, weight;
        Edge(int v1, int v2, int weight);
        Edge();
};

class Graph{
    public:
        int* ranks;
        int* parents;
        int q_vertex, max_edges;
        Edge* edges;
        Graph(int q_vertex, int q_edge);
        void init_graph();
        int find(int vertex);
        void union_(int v1, int v2);
        void add_edges(int v1, int v2, int weight);
        void sort_edges();
        void kruskal();
        void print();
    private:
        int q_edges;

};

Edge::Edge(int v1, int v2, int weight){
    this->v1 = v1;
    this->v2 = v2;
    this->weight = weight;
};

Edge::Edge(){
    v1 = -1;
    v2 = -1;
    weight = 0;
};

Graph::Graph(int q_vertex, int q_edges){
    ranks = new int[q_vertex + 1];
    edges = new Edge[q_edges];
    parents = new int[q_vertex + 1];
    this->q_vertex = q_vertex + 1;
    this->q_edges = 0;
    this->max_edges = q_edges;

};

void Graph::init_graph(){
    for(int i = 0; i < q_vertex; i++){
        ranks[i] = 0;
        parents[i] = -100;
    }
};

int Graph::find(int vertex){
    if(parents[vertex] == -100){
        return vertex;
    }

    parents[vertex] = find(parents[vertex]);
    return parents[vertex];
};

void Graph::union_(int v1, int v2){
    int v1_find = find(v1);
    int v2_find = find(v2);
    if(v1_find == v2_find){
        return;
    }
    if(ranks[v1_find] == ranks[v2_find]){
        parents[v1_find] = v2_find;
        ranks[v2_find]++;
    }
    else if(ranks[v1_find] > ranks[v2_find]){
        parents[v2_find] = v1_find;
    }
    else if(ranks[v1_find] < ranks[v2_find]){
        parents[v1_find] = v2_find;
    }
};

void Graph::add_edges(int v1, int v2, int weight){
    if(q_edges == max_edges){
        return;
    }
    else{
        Edge edge(v1, v2, weight);
        edges[q_edges++] = edge;
    }
};

void Graph::sort_edges(){
    for(int i = 0; i < q_edges; i++){
        for(int j = 0; j < q_edges; j++){
            if(edges[i].weight < edges[j].weight){
                Edge aux = edges[i];
                edges[i] = edges[j];
                edges[j] = aux;
            }
        }
    }
};

void Graph::kruskal(){
    this->sort_edges();
    int weight = 0;
    int v1, v2;
    for(int i = 0; i < q_edges; i++){
        v1 = find(edges[i].v1);
        v2 = find(edges[i].v2);

        if(v1 != v2){
            weight += edges[i].weight;
            union_(v1, v2);
        }
    }
    cout << weight << endl;
};

void Graph::print(){
    for(int i = 0; i < q_edges; i++){
        cout << this->edges << endl;
    }
}

int first_line_vertex(string input_line){
    string q_vertex = "";
    int i = 0;
    while(input_line[i] != ' '){
        q_vertex += input_line[i];
        i++;
    }
    return stoi(q_vertex);
};

int first_line_edges(string input_line){
    string q_edges = "";
    int i = 0;
    while (input_line[i] != ' '){
        i++;
    }
    i++;
    while(unsigned(i) < input_line.size()){
        q_edges += input_line[i];
        i++;
    }
    return stoi(q_edges);
};

int main(){
    int q_vertex, q_edges;
    string first_line = "";
    getline(cin, first_line);
    q_vertex = first_line_vertex(first_line);
    q_edges = first_line_edges(first_line);
    Graph g(q_vertex, q_edges);
    g.init_graph();
    
    for(int i = 0; i < q_edges; i++){
        string input_line = "";
        getline(cin, input_line);
        string v1 = "";
        string v2 = "";
        string weight = "";
        int j = 0;
        int v1_int = 0;
        int v2_int = 0;
        int weight_int = 0;

        while(input_line[j] != ' '){
            v1 += input_line[j];
            j++;
        }
        j++;

        while(input_line[j] != ' '){
            v2 += input_line[j];
            j++;
        }
        j++;

        while(unsigned(j) < input_line.size()){
            weight += input_line[j];
            j++;
        }

        v1_int = stoi(v1);
        v2_int = stoi(v2);
        weight_int = stoi(weight);
        g.add_edges(v1_int, v2_int, weight_int);
    }
    
    g.kruskal();
};