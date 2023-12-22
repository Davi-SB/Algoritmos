#include <iostream>
#include <limits.h>
using namespace std;

#define MAX_SIZE 20

typedef struct {
    int *H;
    int maxSize;
    int size;
} Heap;

Heap* HeapInit(int maxSize) {
    Heap* heap = new Heap;
    heap->H = new int[maxSize+1];
    heap->H[0] = INT_MAX;
    heap->maxSize = maxSize;
    heap->size = 0;
    return heap;
}

void DeleteHeap(Heap* heap) {
    delete heap->H;
    delete heap;
}

void PrintHeap(Heap* heap) {
    for (int i = 1; i < (heap->size+1); i++) {
        cout << "<[" << i << "], " << heap->H[i] << "> ";
    } cout << endl;
}

void HeapBottomUp(Heap* heap) {
    for (int i = (int)(heap->size/2); i >= 1; i--) {        // nos internos
        int k = i;                                          // posicao atual do no
        int v = heap->H[k];                                 // valor do atual no
        bool heaped = false;

        while (!heaped && ((2*k) <= heap->size)) {          // encontra o lugar certo do valor
            int j = 2*k;                                    // posicao do filho a esqueda
            if((j < heap->size) && (heap->H[j] < heap->H[j+1]))  
                j++;                                        // tem dois filhos && seleciona o maior deles
            if(v >= heap->H[j]) heaped = true;              // heaped se valor atual eh >= o maior filho
            else {                                          // otimizacao (evita o swaps)
                heap->H[k] = heap->H[j];                    // coloca o maior filho em H[k]
                k = j;                                      // atualiza k
            }
        }   
        heap->H[k] = v; // termina os "swaps"
    }
    if(heap->H[0] != INT_MAX) cout << "CUIDADO" << endl;
}

void HeapSort(Heap* heap, int k) { // ordena os K maiores elementos
    if(k >= heap->size) k = heap->size-1;
    
    HeapBottomUp(heap);
    PrintHeap(heap);
    cout << endl;
    
    int temp = heap->size;
    while (k--) {
        swap(heap->H[1], heap->H[heap->size]); // manda a root (maior elemento) para o final do array
        heap->size--; // lazy deletion do maior elemento (ordenado)
        HeapBottomUp(heap);
        PrintHeap(heap);
    } cout << endl;
    heap->size = temp;
}

int main() {
    Heap* heap = HeapInit(MAX_SIZE);
    
    heap->H[1] = 1;   heap->size++;
    heap->H[2] = 1;   heap->size++;
    heap->H[3] = 2;   heap->size++;
    heap->H[4] = 3;   heap->size++;
    heap->H[5] = 5;   heap->size++;
    heap->H[6] = 5;   heap->size++;
    heap->H[7] = 6;   heap->size++;
    heap->H[8] = 7;   heap->size++;
    heap->H[9] = 8;   heap->size++;
    heap->H[10] = 10; heap->size++;

    HeapSort(heap, heap->size);
    PrintHeap(heap);
    
    DeleteHeap(heap);
    return 0;
}