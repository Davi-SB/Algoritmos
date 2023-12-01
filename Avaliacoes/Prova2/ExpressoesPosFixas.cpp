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

/*
Ao representar expressões na notação pós-fixa, os operadores aparecem após os operandos. 
Por exemplo, a expressão infixa 3 + (4 * 2) é equivalente à expressão pós-fixa 3 4 2 * +. 
Já a expressão infixa (3 + 4) * 2 é equivalente à expressão pós-fixa 3 4 + 2 *.

Input Specification
A entrada consiste em múltiplas expressões em notação pós-fixa, uma por linha. Todas as 
expressões são bem formadas. Em cada expressão, os operandos e operadores são separados 
por espaços. Os operandos são números inteiros. Os operadores são +, - ou * e todos são 
binários (atuam sobre dois operandos). O final de uma expressão é representado pela 
string “END”. O final da entrada é representado pela string “EOF”.

Output Specification
Para cada expressão, imprima o valor resultante da sua avaliação. O tipo inteiro 
(32 bits) tem precisão suficiente para armazenar o resultado da avaliação de 
qualquer expressão da entrada.

Sample input:
3 4 2 * + END
3 4 + 2 * END
3 4 2 * - END
3 4 - 2 * END
-10 -2 * -10 - END
EOF

Sample output:
11
14
-5
-2
30

*/