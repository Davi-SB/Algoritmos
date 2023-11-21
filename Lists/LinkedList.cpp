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

Node* CreateHeader(Node* nextVal) {
    Node* n = new Node;
    n->Pnext = nextVal;
    return n;
}

LinkedList* CreateList() {
    LinkedList* l = new LinkedList;
    l->curr = l->tail = l->head = CreateHeader(nullptr); // header node
    l->count = 0;
    return l;
}

void Insert(LinkedList* l, E it) { // insere sempre na frente do cursor. nao ele muda de lugar
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

E Remove(LinkedList* l) { // remove o elemento NA FRENTE DO CURSOR
    E it = l->curr->Pnext->element;
    Node* temp = l->curr->Pnext;

    if(l->tail == l->curr->Pnext) l->tail = l->curr;
    l->curr->Pnext = l->curr->Pnext->Pnext;
    l->count--;

    delete temp;
    return it;
}

void PrintList(LinkedList* l) {
    
    Node* temp = l->curr;
    MoveToStart(l);

    cout << "Lista: ";
    while (l->curr != l->tail) {
        Pnext(l);
        cout << l->curr->element << " ";
    } cout << endl;

    l->curr = temp;
    temp = nullptr;
}

void Append(LinkedList* l, E it) { // adiciona no final. nao altera o cursor
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
    l->head = l->tail = l->curr = nullptr;
    delete l; // l eh um ponteiro que foi alocado com new
}

int main() {
    LinkedList* myList = CreateList();

    PrintList(myList);

    Insert(myList, 10);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    Insert(myList, 20);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    Insert(myList, 30);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    Append(myList, 123);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    Pnext(myList);
    Pnext(myList);
    Insert(myList, 555);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    MoveToStart(myList);
    Insert(myList, 1);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    Pnext(myList);
    Pnext(myList);
    Remove(myList);
    PrintList(myList);
    cout << "Curr: " << myList->curr->element << endl; cout << "Head: " << myList->head->Pnext->element << endl; cout << "Tail: " << myList->tail->element << endl << endl;

    DeleteList(myList);
    return 0;
}
