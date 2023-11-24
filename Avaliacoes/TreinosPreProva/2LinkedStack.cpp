#include<iostream>
using namespace std;
#define E int
#define endl '\n'

// 15min

typedef struct node{
    node* Pnext;
    E element;
} Node;

typedef struct{
    Node* top;
    int size;
} LStack;

LStack* CreateStack() {
    LStack* s = new LStack;
    s->top = nullptr;
    s->size = 0;
    return s;
}

Node* CreateNode(E it, Node* nextVal) {
    Node* n = new Node;
    n->element = it;
    n->Pnext = nextVal;
    return n;
}

void Push(LStack* s, E it) {
    s->top = CreateNode(it, s->top);
    s->size++;
}

E Pop(LStack* s) {
    if(s->top == nullptr) return -1;
    int it = s->top->element;
    Node* temp = s->top;

    s->top = s->top->Pnext;
    s->size--;
    delete temp;
    return it;
}

void PrintStack(LStack* s) {
    if(!s->size) return;
    
    Node* temp = s->top;

    for(int i = s->size; i>0; i--) {
        cout << temp->element << " ";
        temp = temp->Pnext;
    } cout << endl;
    temp = nullptr;
}

void DeleteList(LStack* s) {
    while (s->size) {
        Pop(s);
    }
    delete s;
}