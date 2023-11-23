#include <iostream>
using namespace std;

#define E char
#define endl '\n'

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
    return it;
}

void PrintStack(LinkedStack* s) {
    if (!(s == nullptr || s->top == nullptr)) {
        Node* temp = s->top;
        for(int i = s->size; i>0; i--) {
            cout << temp->element; // comeca printando, NAO tem header node
            temp = temp->Pnext;
        } cout << endl;
        temp = nullptr;
    } else cout << endl;
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
    LinkedStack* stack = CreateStack();
    string word="";
    char currChar;

    cin >> word;
    for (int i = static_cast<int>(word.size())-1; i >= 0; i--) {
        currChar = word[i];
        Push(stack, currChar);
        if((stack->size >= 3) && (stack->top->element == 'A') && (stack->top->Pnext->element == 'B') && (stack->top->Pnext->Pnext->element == 'C')) {
            Pop(stack); Pop(stack); Pop(stack); // retira 3, o ABC
        }
    }
    PrintStack(stack);
    DeleteList(stack);;
    return 0;
}

// g++ TakeABCSTACK.cpp -o ABC && ./ABC < input.txt

/* PRINTA AO CONTRARIO
int main() {
    LinkedStack* stack = CreateStack();
    char currChar;
    while(cin >> currChar) {
        Push(stack, currChar);
        if((stack->size >= 3) && (stack->top->element == 'C') && (stack->top->Pnext->element == 'B') && (stack->top->Pnext->Pnext->element == 'A')) {
            Pop(stack); Pop(stack); Pop(stack); // retira 3, o ABC
        }
    }
    PrintStack(stack);
    DeleteList(stack);;
    return 0;
}
*/