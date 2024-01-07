#include <iostream>
#include <limits.h>
using namespace std;

#define MAX_SIZE 5001

// fazer o heapsort ao contrario
// pega os dois menores, soma e esse resultado entra no array
// dps pega os dois menores atuais e soma. vai assim ate acabarem os numeros, (tam-1) vezes
// cada resultado de soma deve ser += ao sumCost

// dado o array inicialmente, o heapify deve ser bottom-up. os proximos, devem ser top down

typedef struct {
    int *H;
    int maxSize;
    int size;
} Heap;

Heap* HeapInit(int maxSize) {
    Heap* heap = new Heap;
    heap->H = new int[maxSize+1];
    heap->H[0] = INT_MIN;
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
        cout << "<[" << i << "], " << heap->H[i] << ">  ";
    } cout << endl;
}

void Heapify(Heap* heap, int i) {
    int k = i;                                          // posicao atual do no
    int v = heap->H[k];                                 // valor do atual no
    bool heaped = false;

    while (!heaped && ((2*k) <= heap->size)) {          // encontra o lugar certo do valor
        int j = 2*k;                                    // posicao do filho a esqueda
        if((j < heap->size) && (heap->H[j] > heap->H[j+1]))  
            j++;                                        // tem dois filhos && seleciona o maior deles
        if(v <= heap->H[j]) heaped = true;              // heaped se valor atual eh <= o maior filho !!!!MIN-HEAP!!!!
        else {                                          // otimizacao (evita o swaps)
            heap->H[k] = heap->H[j];                    // coloca o maior filho em H[k]
            k = j;                                      // atualiza k
        }
    }   
    heap->H[k] = v; // termina os "swaps"
    if(heap->H[0] != INT_MIN) cout << "CUIDADO" << endl;
}

void HeapBottomUp(Heap* heap) {
    for (int i = (int)(heap->size/2); i >= 1; i--) Heapify(heap, i);
}

void HeapSort(Heap* heap, int k) { // ordena os K maiores elementos
    if(k >= heap->size) k = heap->size-1;
    
    nao esquecer//HeapBottomUp(heap);
    //PrintHeap(heap); cout << endl;
    
    int temp = heap->size;
    while (k--) {
        swap(heap->H[1], heap->H[heap->size]); // manda a root (maior elemento) para o final do array
        heap->size--; // lazy deletion do maior elemento (ordenado)
        Heapify(heap, 1);
        //PrintHeap(heap);
    } cout << endl;
    heap->size = temp;
}

int main() {
    int n;
    while (cin >> n && n) {
        Heap* heap = HeapInit(n+1); // +1 so por seguranca
        
        for (int i = 0; i < n; i++) { // coloca os numeros no array do heap
            cin >> heap->H[i+1]; // i+1 para comecar da posicao 1 do array
        }

        HeapBottomUp(heap);
        
        while(n-1) {
            int minor1 = heap->H[heap->size], minor2 = heap->H[heap->size-1]; // armazena os dois menores selecionados
            heap->H[heap->size-1] = minor1 + minor2;
            heap->size--;
            HeapSort(heap, 2); // o heapify deve fazer parte dele e ser o TOP DOWN nesse caso

            n--;
        }

        DeleteHeap(heap);
    }
    
    return 0;
}