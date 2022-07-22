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
        void init();
        int find(int vertex);
        void _union(int v1, int v2);
        void addEdges(int v1, int v2, int weight);
        void sortEdges();
        void kruskal();
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

void Graph::init(){
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

void Graph::_union(int v1, int v2){
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

void Graph::addEdges(int v1, int v2, int weight){
    if(q_edges == max_edges){
        return;
    }
    else{
        Edge edge(v1, v2, weight);
        edges[q_edges++] = edge;
    }
};

void Graph::sortEdges(){
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
    this->sortEdges();
    int weight = 0;
    int v1, v2;
    for(int i = 0; i < q_edges; i++){
        v1 = find(edges[i].v1);
        v2 = find(edges[i].v2);

        if(v1 != v2){
            weight += edges[i].weight;
            _union(v1, v2);
        }
    }
    cout << weight << endl;
}

int main(){
    Graph g(10, 12);
    g.init();
    g.addEdges(1, 2, 1);
    g.addEdges(2, 3, 3);
    g.addEdges(3, 4, 1);
    g.addEdges(4, 5, 1);
    g.addEdges(5, 6, 4);
    g.addEdges(6, 7, 2);
    g.addEdges(7, 8, 1);
    g.addEdges(4, 8, 3);
    g.addEdges(8, 9, 2);
    g.addEdges(9, 3, 1);
    g.addEdges(9, 10, 1);
    g.addEdges(1, 10, 3);

    g.kruskal();
};