#include <iostream>
using namespace std;
#define E char

// Broken Keyboard (a.k.a. Beiju Text) - SOLVED
// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3139

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

void Pnext(LinkedList* l) {
    if(l->curr != l->tail) l->curr = l->curr->Pnext;
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
    LinkedList* LList = CreateList();
    string line="";
    bool atStart= true;
    while (getline(cin, line)) {
        for (int i=0; i< static_cast<int>(line.size()); i++) {
            if(line[i] == '[') { MoveToStart(LList); atStart = true; }
            else if(line[i] == ']') { MoveToEnd(LList); atStart = false; }
            else {
                if(atStart) {
                    Insert(LList, line[i]);
                    Pnext(LList);
                }
                else {
                    Append(LList, line[i]);
                }
            }
        }
        PrintList(LList);
        line.clear();
        DeleteList(LList);
        LList = CreateList();
    }
    DeleteList(LList);
    return 0;
}

/*
You’re typing a long text with a broken keyboard. Well it’s not so badly broken. The only problem
with the keyboard is that sometimes the “home” key or the “end” key gets automatically pressed
(internally).
You’re not aware of this issue, since you’re focusing on the text and did not even turn on the
monitor! After you finished typing, you can see a text on the screen (if you turn on the monitor).
In Chinese, we can call it Beiju. Your task is to find the Beiju text.

Input
There are several test cases. Each test case is a single line containing at least one and at most 100,000
letters, underscores and two special characters ‘[’ and ‘]’. ‘[’ means the “Home” key is pressed
internally, and ‘]’ means the “End” key is pressed internally. The input is terminated by end-of-file
(EOF).

Output
For each case, print the Beiju text on the screen.

Sample Input
This_is_a_[Beiju]_text
[[]][][]Happy_Birthday_to_Tsinghua_University

Sample Output
BeijuThis_is_a__text
Happy_Birthday_to_Tsinghua_University
*/