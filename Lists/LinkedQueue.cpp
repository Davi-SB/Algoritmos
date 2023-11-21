#include <iostream>
using namespace std;

#define E int

typedef struct node {
    E element;
    node* Pnext;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} LinkedQueue; 

Node* CreateHeader(Node* nextVal) {
    Node* n = new Node;
    n->Pnext = nextVal;
    return n;
}

Node* CreateNode(E it, Node* nextVal) {
    Node* n = new Node;
    n->element = it;
    n->Pnext = nextVal;
    return n;
}

LinkedQueue* CreateQueue() {
    LinkedQueue* q = new LinkedQueue;
    q->front = q->rear = CreateHeader(nullptr); // header node
    q->size = 0;
    return q;
}

void Enqueue(LinkedQueue* q, E it) { // "append"
    q->rear->Pnext = CreateNode(it, nullptr);
    q->rear = q->rear->Pnext;
    q->size++;
}

E Dequeue(LinkedQueue* q) { // remove o primeiro, q->front->Pnext
    if(q->size == 0) { cout << "error\n"; return -1; }
    E it = (q->front)->Pnext->element;
    
    Node* temp = (q->front)->Pnext; // (q->front) eh o header node
    (q->front)->Pnext = (q->front)->Pnext->Pnext;
    delete temp;
    
    if((q->front)->Pnext == nullptr) q->rear = q->front; // empty queue
    q->size--;
    return it;
}

void PrintQueue(LinkedQueue* q) {
    if (q == nullptr || q->front == nullptr) { cout << "Queue is empty" << endl; return; }

    Node* temp = q->front;

    cout << "Queue: ";
    for(int i = q->size; i>0; i--) {
        temp = temp->Pnext; // comeca indo pro prox, o primeiro eh o header node
        cout << temp->element << " ";
    } cout << endl;
    temp = nullptr;
}

void DeleteList(LinkedQueue* q) { // libera memoria alocada para a lista e os nodes
    while (q->size > 0) {
        Node* temp = q->front; // temp recece a front inicial/atual
        q->front = q->front->Pnext; // front passa a apontar para o proximo
        delete temp;
        q->size--;
    }
    q->front = q->rear = nullptr;
    delete q; // q eh um ponteiro que foi alocado com new
}

int main() {
    LinkedQueue* Queue = CreateQueue();

    for (int j = 1; j <= 5; j++) { // 1 2 3 4 5
        Enqueue(Queue, j);
        PrintQueue(Queue);
        cout << "Front: " << Queue->front->element << endl << "Rear: " << Queue->rear->element << endl << endl; 
    }

    Dequeue(Queue);
    PrintQueue(Queue);
    cout << "Front: " << Queue->front->element << endl << "Rear: " << Queue->rear->element << endl << endl;    
    
    Dequeue(Queue);
    PrintQueue(Queue); // 3 4 5
    cout << "Front: " << Queue->front->element << endl << "Rear: " << Queue->rear->element << endl << endl;    

    DeleteList(Queue);;
    return 0;
}