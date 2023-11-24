#include<iostream>
using namespace std;
#define E int
#define endl '\n'

// 15min

typedef struct n{
    n* Pnext;
    int element;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} LQueue;

Node* CreateNode(E it, Node* nextVal) {
    Node* n = new Node;
    n->element = it;
    n->Pnext = nextVal;
    return n;
}

Node* CreateHeader(Node* nextVal) {
    Node* n = new Node;
    n->Pnext = nextVal;
    return n;
}

LQueue* CreateQueue() {
    LQueue* q = new LQueue;
    q->front = q->rear = CreateHeader(nullptr);
    q->size = 0;
    return q;
}

void Enqueue(LQueue* q, E it) {
    q->rear->Pnext = CreateNode(it, nullptr);
    q->rear = q->rear->Pnext;
    q->size++;
}

E Dequeue(LQueue* q) {
    if(!q->size) return 0;
    E it = q->front->Pnext->element;
    Node* temp = q->front->Pnext;
    q->front->Pnext = q->front->Pnext->Pnext;
    if(q->front->Pnext == nullptr) q->rear = q->front;
    q->size--;
    delete temp;
    return it;
}

void DeleteList(LQueue* q) {
    while (q->size) {
        Dequeue(q);
    }
    delete q;
}

void PrintList_DeleteList(LQueue* q) { // MTO FORTE BOM DMS ESSA TA
    while (q->size) {
        cout << Dequeue(q);
    } cout << endl;
    delete q->front;
    delete q;
}

void PrintList(LQueue* q) {
    Node* temp = q->front->Pnext;
    for (int i = 0; i < q->size; i++) {
        cout << temp->element;
        temp = temp->Pnext;
    } cout << endl;
    temp = nullptr;    
}