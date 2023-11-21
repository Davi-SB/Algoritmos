#include<iostream>
using namespace std;

#define E int

typedef struct {
    int maxSize, listSize, curr; // maxSize --> capacidade max // listSize --> ocupado atualmente
    E* array;
} ArrayList;

ArrayList* CreateList(int size) {
    ArrayList* l = new ArrayList;
    l->maxSize = size;
    l->listSize = l->curr = 0;
    l->array = new E[size];
    return l;
}

void Insert(ArrayList* l, E it) {
    if(l->listSize >= l->maxSize) { cout << "erro\n"; return; }
    
    for (int i = l->listSize; i > l->curr; i--) {
        l->array[i] = l->array[i-1]; // shift right
    }
    l->array[l->curr] = it;
    l->listSize++;
}

void MoveToStart(ArrayList* l) {
    l->curr = 0;
}

void MoveToEnd(ArrayList* l) { // nao se refere ao ultimo indice!!! Move para o primeiro indice vazio
    l->curr = l->listSize;
}

void Previous(ArrayList* l) {
    if(l->curr != 0) l->curr--;
}

void Next(ArrayList* l) {
    if(l->curr < l->listSize) l->curr++; // so permite o next andar ate o MoveToEnd
}

void Append(ArrayList* l, E it) {
    if(l->listSize >= l->maxSize) { cout << "erro\n"; return; }
    int temp = l->curr;
    MoveToEnd(l);
    Insert(l, it);
    l->curr = temp;
}

E Remove(ArrayList* l) {
    if((l->curr < 0) || (l->curr >= l->listSize)) { cout << "erro\n"; return -1; }
    
    E it = l->array[l->curr];
    for (int i = l->curr; i < (l->listSize-1); i++) {
        l->array[i] = l->array[i+1];
    }
    l->listSize--;
    return it;
}

void PrintList(ArrayList* l) {
    cout << "Array: ";
    for (int i = 0; i < l->listSize; i++) {
        cout << l->array[i] << " ";
    } cout << endl;
}

int main() {
    ArrayList* Array = CreateList(10);

    for (int j = 1; j <= 5; j++) { // 5 4 3 2 1
        Insert(Array, j);
        PrintList(Array);
    }
    
    Append(Array, 10);
    PrintList(Array); // 5 4 3 2 1 10

    MoveToStart(Array);
    Remove(Array);
    PrintList(Array); // 4 3 2 1 10

    Next(Array);
    Next(Array);
    Remove(Array);
    PrintList(Array); // 4 3 1 10

    MoveToEnd(Array);
    Previous(Array);
    Remove(Array);
    PrintList(Array); // 4 3 1

    delete Array;
    return 0;
}