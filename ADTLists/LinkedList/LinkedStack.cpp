#include <iostream>
using namespace std;

#define E int

typedef struct node {
    E element;
    node* Pnext;
} Node;

typedef struct {
    Node* top;
    int size;
} LinkedStack;

LinkedStack* CreateStack() {
    LinkedStack* s = new LinkedStack;
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

void Push (LinkedStack* s, E it) {
    s->top = CreateNode(it, s->top);
    s->size++;
}

E Pop (LinkedStack* s) { // remove top->element
    if(s->top == nullptr) { cout << "erro\n"; return '1'; }
    E it = s->top->element;

    Node* temp = s->top; // guarda o endereco do top atual
    s->top = s->top->Pnext;
    delete temp; // libera ele

    s->size--;
    delete temp;
    return it;
}

void PrintStack(LinkedStack* s) {
    if (s == nullptr || s->top == nullptr) { cout << "Stack is empty" << endl; return; }

    Node* temp = s->top;

    cout << "Stack: ";
    for(int i = s->size; i>0; i--) {
        cout << temp->element << " "; // comeca printando, NAO tem header node
        temp = temp->Pnext;
    } cout << endl;
    temp = nullptr;
}

void DeleteList(LinkedStack* s) { // libera memoria alocada para a lista e os nodes
    while (s->size > 0) {
        Node* temp = s->top; // temp recece a top inicial/atual
        s->top = s->top->Pnext; // top passa a apontar para o proximo
        delete temp;
        s->size--;
    }
    s->top = nullptr;
    delete s; // s eh um ponteiro que foi alocado com new
}

int main() {
    LinkedStack* Stack = CreateStack();

    for (int j = 1; j <= 5; j++) { // 5 4 3 2 1
        Push(Stack, j);
        PrintStack(Stack);
        cout << "Top: " << Stack->top->element << endl << endl;    
    }

    Pop(Stack);
    PrintStack(Stack);
    cout << "Top: " << Stack->top->element << endl << endl;    
    
    Pop(Stack);
    PrintStack(Stack); // 3 2 1
    cout << "Top: " << Stack->top->element << endl << endl;    

    DeleteList(Stack);;
    return 0;
}