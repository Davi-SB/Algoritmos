#include <iostream>
using namespace std;
#define E char
#define endl '\n'

// Transform the expression - SOLVED
// https://www.spoj.com/problems/ONP/

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
    string line="";
    int repeat; 
    cin >> repeat; 
    cin.ignore();

    for (int j = 0; j < repeat; j++) {
        getline(cin, line);
        for (int i = 0; i < static_cast<int>(line.size()); i++) {
            if(line[i] != '(') {
                if((line[i] >= 'a') && (line[i] <= 'z')) {
                    cout << line[i];
                }
                else if(line[i] == ')') {
                    cout << Pop(Stack);
                }
                else { //if((line[i]=='+')||(line[i]=='-')||(line[i]=='*')||(line[i]=='/')||(line[i]=='^')) 
                    Push(Stack, line[i]);
                }
            }
        }
        cout << endl;
        line.clear();
    }
    DeleteList(Stack);;
    return 0;
}

// g++ TransformTheExpression.cpp -o TTE && ./TTE < input.txt

/*
stack com os operadores
( sao completamente ignorados
) pop a stack
numeros sao printados assim que escaneados
*/