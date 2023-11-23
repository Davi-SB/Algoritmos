#include <iostream>
using namespace std;

#define E char
#define endl '\n'

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
    while (l->curr != l->tail) {
        Pnext(l);
        cout << l->curr->element;
    } cout << endl;
    l->curr = temp;
    temp = nullptr;
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

    LinkedList* LList = CreateList();
    char currChar;
    int cont=0;
    int moved=2;

    while (cin >> currChar) { // armazena a entrada
        Insert(LList, currChar);
        Pnext(LList);
        cont++;
    }
    MoveToStart(LList);
    //PrintList(LList);

    while(moved && LList->count) {
        while((LList->curr->Pnext != nullptr) && (LList->curr->Pnext->Pnext != nullptr) && (LList->curr->Pnext->Pnext->Pnext != nullptr)) {

            if((LList->curr->Pnext->element == 'A')&&(LList->curr->Pnext->Pnext->element == 'B')&&(LList->curr->Pnext->Pnext->Pnext->element == 'C')) {
                for (int i = 0; i < 3; i++) { // roda 3 vezes
                    Remove(LList);
                }
                cont -= 3;
                moved=2;
            }
            else {
                Pnext(LList);
                cont--;
            }
        }
        moved--;
        //PrintList(LList);
        MoveToStart(LList);
    }
    PrintList(LList);
    
    DeleteList(LList);
    return 0;
}

// g++ TakeABC.cpp -o ABC && ./ABC < input.txt
// https://atcoder.jp/contests/abc328/tasks/abc328_d