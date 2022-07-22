/* 
 * Programa: AlgoritmosDeOrdenacao.c;
 * Autor: Daniel Machado;
 * DRE: 121046088;
 * Descrição: Executa os algoritmos de ordenação BubbleSort, MergeSort e QuickSort.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int bubbleSort (int *v, int n);

int mergeSort (int *v, int start, int end);

int Merge (int *v, int start, int center, int end);

int quickPartition (int *v, int start, int end);

int quickSort (int *v, int start, int end);

int main (int argc, char *argv[]){
    
    int n = atoi(argv[2]), i = 0, j = 0, tam = 0, aux = 0, t = 0;
    char modo = 'b';
    int *v;
    srand(time(NULL));
    v = (int *) malloc(n * sizeof(int));

    if(v != NULL){
        for(i = 0; i < n; i++){
            v[i] = rand() % 10000;
        }
    }

    if(argc > 3){
        modo = argv[3][1];
    }

    /* bubble sort */
    if(modo == 'b'){
        /* cálculo do tempo de execução */
        t = clock();
        bubbleSort(v, n);
        t = clock() - t;
        printf("---Bubble Sort---\n");
        printf("Vetor ordenado!\nTempo de execucao: %.4fs", ((double)t)/((CLOCKS_PER_SEC)));
    }

    /* merge sort */
    if(modo == 'm'){
        /* cálculo do tempo de execução */
        t = clock();
        mergeSort(v, 0, n - 1);
        t = clock() - t;
        printf("---Merge Sort---\n");
        printf("Vetor ordenado!\n");
        printf("[ ");
        for(int i = 0; i < n; i++){
            printf("%d ", v[i]);
        }
        printf("]\n");
        printf("Tempo de execucao: %.4fs", ((double)t)/((CLOCKS_PER_SEC)));
    }

    /* quick sort */
    if(modo == 'q'){
        /* cálculo do tempo de execução */
        t = clock();
        quickSort(v, 0, n -1);
        t = clock() - t;
        printf("Vetor ordenado!\n");
        printf("[ ");
        for(int i = 0; i < n; i++){
            printf("%d ", v[i]);
        }
        printf("]\n");
        printf("Tempo de execucao: %.4fs", ((double)t)/((CLOCKS_PER_SEC)));
    }

    return 0;
}

int bubbleSort (int *v, int n){
    int i = 0, j = 0, size = n, aux = 0;
    int *b = v;

    for(i = 0; i < size; i++){
        for(j = 0; j < (size - 1); j++){
            if(b[j] > b[j + 1]){
                aux = b[j];
                b[j] = b[j + 1];
                b[j + 1] = aux;
            }
        }
    }
    return 0;
}

int mergeSort (int *v, int start, int end){
    int center = 0;
    if(start < end){
        center = floor((start + end) / 2);
        mergeSort(v, start, center);
        mergeSort(v, center + 1, end);
        Merge(v, start, center, end);
    }
    return 0;
}

int Merge (int *v, int start, int center, int end){
    int *temp, firstSide = 0, secondSide = 0, size = 0, i = 0, j = 0, k = 0;
    int end1 = 0, end2 = 0;
    size = (end - start) + 1;
    firstSide = start;
    secondSide = center + 1;
    temp = (int *) malloc(size * sizeof(int));
    if(temp != NULL){
        for(i = 0; i < size; i++){
            if(!end1 && !end2){
                if(v[firstSide] < v[secondSide]){
                    temp[i] = v[firstSide++];
                }
                else{
                    temp[i] = v[secondSide++];
                }
                if(firstSide > center){
                    end1 = 1;
                }
                if(secondSide > end){
                    end2 = 1;
                }
            }
            else{
                if(!end1){
                    temp[i] = v[firstSide++];
                }
                else{
                    temp[i] = v[secondSide++];
                }
            }
        }
        for(j = 0, k = start; j < size; j++, k++){
            v[k] = temp[j];
        }
    }
    free(temp);
    return 0;
}

int quickPartition (int *v, int start, int end){
    int pivot = v[end];
    int k = start;
    int aux = 0, i = 0;

    for (i = start; i < end; i++){
        if (v[i] <= pivot){
            aux = v[i];
            v[i] = v[k];
            v[k] = aux;
            k++;
        }
    }

    aux = v[k];
    v[k] = v[end];
    v[end] = aux;
    return k;
}

int quickSort (int *v, int start, int end){
    if (start < end){
        int pivot = quickPartition(v, start, end);
        quickSort(v, start, pivot - 1);
        quickSort(v, pivot + 1, end);
    }

    return 0;
}
