#include<iostream>
using namespace std;

#define E int

typedef struct {
    int maxSize, size; // maxSize --> capacidade max // size --> ocupado atualmente
    E* stack;
} ArrayStack;

ArrayStack* CreateStack(int size) {
    ArrayStack* s = new ArrayStack;
    s->maxSize = size;
    s->size = 0;
    s->stack = new E[size];
    return s;
}

void Push(ArrayStack* l, E it) {
    if(l->size >= l->maxSize) { cout << "erro\n"; return; }
    l->stack[l->size++] = it;
}

E Pop(ArrayStack* l) {
    if(l->size <= 0) { cout << "erro\n"; return -1; }
    
    E it = l->stack[l->size-1];
    l->size--;
    return it;
}

void PrintList(ArrayStack* l) {
    cout << "Stack: ";
    for (int i = 0; i < l->size; i++) {
        cout << l->stack[i] << " ";
    } cout << endl;
}

int main() {
    ArrayStack* Stack = CreateStack(10);

    for (int j = 1; j <= 5; j++) { // 5 4 3 2 1
        Push(Stack, j);
        PrintList(Stack);
    }
    
    for (int j = 1; j <= 6; j++) { // 6 --> teste invasao memoria 
        Pop(Stack);
        PrintList(Stack);
    }

    delete Stack;
    return 0;
}