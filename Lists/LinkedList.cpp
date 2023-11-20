#include <iostream>
using namespace std;

#define E int

typedef struct node {
    E element;
    node* Pnext;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    Node* curr;
    int count;
} LinkedList;

Node* CreateNode(E it, Node* nextVal) {
    Node* n = new Node;
    n->element = it;
    n->Pnext = nextVal;
    return n;
}

LinkedList* CreateList() {
    LinkedList* l = new LinkedList;
    l->curr = l->tail = l->head = CreateNode(static_cast<E>(97), nullptr); // header node
    l->count = 0;
    return l;
}

void Insert(LinkedList* l, E it) {
    l->curr->Pnext = CreateNode(it, l->curr->Pnext);
    if(l->tail == l->curr) l->tail = l->curr->Pnext;
    l->count++;
}

void MoveToStart(LinkedList* l) {
    l->curr = l->head;
}

void MoveToEnd(LinkedList* l) {
    l->curr = l->tail;
}

void Previous(LinkedList* l) {
    if(l->curr == l->head) return;
    Node* temp = l->head;
    while (temp->Pnext != l->curr) {
        temp = temp->Pnext;
    }
    l->curr = temp;
}

void Pnext(LinkedList* l) {
    if(l->curr != l->tail) l->curr = l->curr->Pnext;
}

E Remove(LinkedList* l) {
    E it = l->curr->Pnext->element;
    Node* temp = l->curr->Pnext;

    if(l->tail == l->curr->Pnext) l->tail = l->curr;
    l->curr->Pnext = l->curr->Pnext->Pnext;
    l->count--;

    delete temp;
    return it;
}

void PrintList(LinkedList* l) {
    MoveToStart(l);

    cout << "Lista: ";
    while (l->curr != l->tail) {
        Pnext(l);
        cout << l->curr->element << " ";
    } 
    cout << endl;
}

void Append(LinkedList* l, E it) {
    Node* temp = l->curr;
    l->curr = l->tail;
    Insert(l, it);
    l->curr = temp;
}

void DeleteList(LinkedList* l) { // libera memoria alocada para a lista e os nodes
    MoveToStart(l); // importante comecar do comeco da lista
    while (l->head != nullptr) {
        Node* temp = l->head; // temp recece a head inicial/atual
        l->head = l->head->Pnext; // head passa a apontar para o proximo
        delete temp;
    }
    delete l; // l eh um ponteiro que foi alocado com new
}

int main() {
    LinkedList* myList = CreateList();

    /*
    Insert(myList, 10);
    Insert(myList, 20);
    Insert(myList, 30); // 50, 40, 30, 20, 10
    Insert(myList, 40);
    Insert(myList, 50);
    */

    for (int i = 1; i <= 5; i++) {
        Insert(myList, i*10);
        MoveToEnd(myList);
    }

    PrintList(myList);

    myList->curr = myList->head;
    Remove(myList);
    PrintList(myList);

    DeleteList(myList);
    return 0;
}
