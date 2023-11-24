#include<iostream>
#include<string>
using namespace std;
#define E int
#define endl '\n'

typedef struct node{
    int element;
    node* Pnext;
} Node;

typedef struct {
    Node* top;
    int size;
} Stack;

Node* CreateNode(int it, Node* nextVal){
    Node* n = new Node;
    n->element = it;
    n->Pnext = nextVal;
    return n;
}

Stack* CreateStack() {
    Stack* s = new Stack;
    s->top = nullptr;
    s->size = 0;
    return s;
}

void Push(Stack* s, int it) {
    s->top = CreateNode(it, s->top);
    s->size++;
}

int Pop(Stack* s) {
    if(s->top == nullptr) return 0;
    int it = s->top->element;
    Node* temp = s->top;
    s->top = s->top->Pnext;
    s->size--;
    delete temp;
    return it; 
}

void DeleteStack(Stack* s) {
    while (s->size) {
        Pop(s);
    }
    s->top = nullptr;
}

void Teste(Stack* s) {
    for (int i = 1; i <= 5; i++) {
        Push(s, i);
    }
    for (int i = 1; i <= 5; i++) {
        int aux = Pop(s);
        cout << aux;
    } cout << endl;
    DeleteStack(s);
}

// numero --> push
// operador --> realiza a operacao com os dois numeros do topo da lista
int main() {
    Stack* stack = CreateStack();
    string currStr = "";

    while ((cin >> currStr) && (currStr != "EOF")) {
        while (currStr != "END") {
            if(currStr == "-") {
                int a=Pop(stack), b=Pop(stack);
                int total = (b - a);  // ORDEM CONTRARIA
                Push(stack, total);
            }
            else if(currStr == "+") {
                int a=Pop(stack), b=Pop(stack);
                int total = (b + a);
                Push(stack, total);
            }
            else if(currStr == "*") {
                int a=Pop(stack), b=Pop(stack);
                int total = (a * b);
                Push(stack, total);
            }
            else { // numero
                Push(stack, stoi(currStr));
            }
            cin >> currStr;
        }
        cout << Pop(stack) << endl;
        currStr.clear();
        DeleteStack(stack);
    }
    delete stack;
    return 0;
}
// g++ EP2.cpp -o EP2
// g++ EP2.cpp -o EP2 && ./EP2 < input.txt