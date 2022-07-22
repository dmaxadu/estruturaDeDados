#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 1000
#define ERROR printf("It's empty!")

typedef struct _edge edge;

typedef struct _edge{
    int quantity;
    int count;
    edge* next;
} edge;

typedef struct _graph graph;

typedef struct _graph{
    edge **edgeGraph;
    int size;
} graph;

edge* start(){
    edge* pt = (edge*) malloc(sizeof(edge));
    pt->next = NULL;
    pt->count = 0;
    return pt;
}

void consGraph(graph *gph, int nEdges){
    gph->edgeGraph =calloc(nEdges+1, sizeof(edge*));
    gph->size = nEdges;
    for(int i = 1; i<gph->size+1; i++){
      gph->edgeGraph[i] = start();
    }

}

void addOn(edge* ptArray, int quantity){
    edge* new = (edge*) malloc(sizeof(edge));
    new->quantity = quantity;
    new->next = ptArray->next;
    ptArray->next = new;
}

void printArray(edge* ptArray){
    edge* aux = ptArray->next;
    if(aux==NULL) ERROR;
    while(aux!=NULL){
        printf("%d  ", aux->quantity);
        aux = aux->next;
    }
}

void printGraph(graph* gph){
    for(int i = 1; i<gph->size+1; i++){
        printf("%d 's child: ", i);
        printArray(gph->edgeGraph[i]);
        printf("\n");
    }
}

void addEdge(graph *gph, edge *father, int child){
    addOn(father, child);
    gph->edgeGraph[child]->count++;  
}

void remEdge(graph *gph, int index){
    
    edge *aux = gph->edgeGraph[index]->next;
    while(aux!=NULL){
        gph->edgeGraph[aux->quantity]->count--;
        aux= aux->next;
    }
    free(gph->edgeGraph[index]->next);
    gph->edgeGraph[index]->next = NULL;
    gph->edgeGraph[index]->count = -1;
}

int emptyGraph(graph *gph){
    for (int i = 1; i<gph->size+1; i++){
        if(gph->edgeGraph[i]->count >-1) return 0;
    }
    return 1;
}

void topSort(graph *gph){

    while(!emptyGraph(gph)){
        for (int i = 1; i<gph->size+1; i++){
            if(gph->edgeGraph[i]->count == 0){
                printf("%d ", i);
                remEdge(gph, i);
                break;
            }
        }
    }

}


void topSortUtil(graph *gph){

    while(!emptyGraph(gph)){
        for (int i = 1; i<gph->size+1; i++){
            if(gph->edgeGraph[i]->count == 0){
                printf("%d ", i);
                remEdge(gph, i);
            }
        }
    }

}

int main(){

    graph gph, gphCopy;
    int i = 1, nEdges;
    char *input, *result;
    char *limiters = " \n";

    fgets(input, TAM, stdin);
    nEdges = atoi(strtok(input, limiters));

    consGraph(&gph, nEdges);
    consGraph(&gphCopy, nEdges);

    for(int i = 1; i<nEdges+1; i++){
        fgets(input, TAM, stdin);
        result = strtok(input, limiters);

        while(result!=NULL){
            if(strcmp(result, "\\n")==0){
                result = strtok(NULL, limiters);
                break;
            }
            addEdge(&gph, gph.edgeGraph[i], atoi(result));
            addEdge(&gphCopy, gphCopy.edgeGraph[i], atoi(result));
            result = strtok(NULL, limiters);
        }
    }
    
    topSort(&gph);

    return 0;
}