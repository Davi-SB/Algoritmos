#include <iostream>
#include <limits.h>
using namespace std;

#define MAX_SIZE 30

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

void HeapTopDown(Heap* heap, int k) {
    heap->size++;
    heap->H[heap->size] = k;
    
    int i = heap->size;
    while ((i > 1) && (heap->H[i] > heap->H[(i/2)])) { //filho maior q o pai
        swap(heap->H[i], heap->H[(i/2)]);
        i /= 2;
    }
}

int main() {
    Heap* heap = HeapInit(MAX_SIZE);
    
    HeapTopDown(heap, 1); PrintHeap(heap);
    HeapTopDown(heap, 5); PrintHeap(heap);
    HeapTopDown(heap, 8); PrintHeap(heap);
    HeapTopDown(heap, 5); PrintHeap(heap);
    HeapTopDown(heap, 3); PrintHeap(heap);
    HeapTopDown(heap, 4); PrintHeap(heap);
    HeapTopDown(heap, 9); PrintHeap(heap);

    PrintHeap(heap);    
    DeleteHeap(heap);
    return 0;
}