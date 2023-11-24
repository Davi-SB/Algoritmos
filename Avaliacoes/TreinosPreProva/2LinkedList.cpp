#include<iostream>
using namespace std;
#define E int
#define endl '\n'

// 40min

typedef struct node{
    E element;
    node* Pnext;
} Node;

typedef struct{
    Node* head;
    Node* tail;
    Node* curr;
    int count;
} LinkedList;

Node* CreateHeader(Node* nextVal) {
    Node* n = new Node;
    n->Pnext = nextVal;
    return n;
}

Node* CreateNode(E it, Node* nextVal) {
    Node* n = new Node;
    n->Pnext = nextVal;
    n->element = it;
    return n;
}

LinkedList* CreateList() {
    LinkedList* l = new LinkedList;
    l->curr = l->tail = l->head = CreateHeader(nullptr);
    l->count = 0;
    return l;
}

void Insert(LinkedList* l, E it) {
    // insere sempre na frente do cursor. nao ele muda de lugar
    l->curr->Pnext = CreateNode(it, l->curr->Pnext);
    if(l->tail == l->curr) l->tail = l->curr->Pnext;
    l->count++;
}

void MoveToStart(LinkedList* l) {
    l->curr = l->head;
}

void MoveToEnd(LinkedList* l) { // !!!
    l->curr = l->tail;
}

void Prev(LinkedList* l) {
    if(l->curr == l->head) return;
    Node* temp = l->head;
    while (temp->Pnext != l->curr) {
        temp = temp->Pnext;
    }
    l->curr = temp;
}

void Next(LinkedList* l) {
    if(l->curr != l->tail) l->curr = l->curr->Pnext;
}

void Append(LinkedList* l, E it) { // !!!
    Node* temp = l->curr;

    MoveToEnd(l);
    Insert(l, it);

    l->curr = temp;
    temp = nullptr;
}

E Remove(LinkedList* l) { // !!!!!!!!!!!!!!
     // remove o elemento NA FRENTE DO CURSOR
    if(l->curr->Pnext == nullptr) return -1;
    E it = l->curr->Pnext->element;
    Node* temp = l->curr->Pnext;

    if (l->tail == l->curr->Pnext) l->tail = l->curr;
    l->curr->Pnext = l->curr->Pnext->Pnext; 
    l->count--;

    delete temp;
    return it;
}

void DeleteList(LinkedList* l) { // !!!!!!!!!!!!!!
    MoveToStart(l);
    while (l->head != nullptr) {
        Node* temp = l->head;
        l->head = l->head->Pnext;
        delete temp;
    }
    l->head = l->tail = l->curr = nullptr;
    delete l;
}

void PrintList(LinkedList* l) { // !!!!!!!!!!!!!!
    Node* temp = l->curr;
    MoveToStart(l);

    while (l->curr != l->tail) {
        Next(l);
        cout << l->curr->element << " ";
    } cout << endl;

    l->curr = temp;
    temp = nullptr;
}