#include <iostream>
#include <limits.h>
using namespace std;

// SOLVED

#define MAX_SIZE 20
#define E char

typedef struct {
    int rate;
    string color, brand;
} Model;

typedef struct {
    Model *H;
    int maxSize;
    int size;
} Heap;

typedef struct avlnode {
    int key, height;
    string brand, color;
    avlnode *left, *right; 
} AVLNode;

typedef struct {
    AVLNode *root;
    int count;
} AVL;


Heap* HeapInit(int maxSize) {
    Heap* heap = new Heap;
    heap->H = new Model[maxSize+1];
    heap->H[0].rate = INT_MAX;
    heap->maxSize = maxSize;
    heap->size = 0;
    return heap;
}

void DeleteHeap(Heap* heap) {
    delete[] heap->H;
    delete heap;
}

void Heapify(Heap* heap, int i) {
    int k = i;                                          // posicao atual do no
    Model v = heap->H[k];                                 // valor do atual no
    bool heaped = false;

    while (!heaped && ((2*k) <= heap->size)) {          // encontra o lugar certo do valor
        int j = 2*k;                                    // posicao do filho a esqueda
        if((j < heap->size) && (heap->H[j].rate < heap->H[j+1].rate))  
            j++;                                        // tem dois filhos && seleciona o maior deles
        if(v.rate >=  heap->H[j].rate) heaped = true;              // heaped se valor atual eh >= o maior filho
        else {                                          // otimizacao (evita o swaps)
            heap->H[k] = heap->H[j];                    // coloca o maior filho em H[k]
            k = j;                                      // atualiza k
        }
    }   
    heap->H[k] = v; // termina os "swaps"
    if(heap->H[0].rate != INT_MAX) cout << "CUIDADO" << endl;
}

void HeapBottomUp(Heap* heap) {
    for (int i = (int)(heap->size/2); i >= 1; i--) Heapify(heap, i);
}

void HeapSort(Heap* heap, int k) { // ordena os K maiores elementos
    if(k >= heap->size) k = heap->size-1;
    
    HeapBottomUp(heap);

    int temp = heap->size;
    while (k--) {
        swap(heap->H[1], heap->H[heap->size]); // manda a root (maior elemento) para o final do array
        heap->size--; // lazy deletion do maior elemento (ordenado)
        Heapify(heap, 1);
    } cout << endl;
    heap->size = temp;
}

AVLNode* CreateAVLNode(int k, string brand, string color) {
    AVLNode* n = new AVLNode;
    n->key = k;
    n->height = 0;
    n->brand = brand;
    n->color = color;
    n->left = n->right = nullptr;
    return n;
} 

AVL* CreateAVL() {
    AVL* avl = new AVL;
    avl->count = 0;
    avl->root = nullptr;
    return avl; 
}

int h(AVLNode* rt) {
    if(rt == NULL) return -1;
    return rt->height;
}

AVLNode* RightRotate(AVLNode* rt) {
    AVLNode *l  = rt->left;
    AVLNode *lr = l->right;
    l->right = rt;
    rt->left  = lr;
    rt->height = 1 + max(h(rt->left), h(rt->right));
    l->height =  1 + max(h( l->left), h( l->right));
    return l;
}

AVLNode* LeftRotate(AVLNode* rt) {
    AVLNode *r  = rt->right;
    AVLNode *rl = r->left;
    r->left  = rt;
    rt->right = rl;
    rt->height = 1 + max(h(rt->left), h(rt->right));
    r->height =  1 + max(h( r->left), h( r->right));
    return r;
}

int GetBalance(AVLNode* rt) {
    if(rt == NULL) return 0;
    return (h(rt->left) - h(rt->right)); // balance factor
}

AVLNode* InsertHelp(AVLNode* rt, int k, string brand, string color) {
    if(rt == nullptr) return CreateAVLNode(k, brand, color);
    if(rt->key > k) rt->left = InsertHelp(rt->left, k, brand, color);
    else rt->right = InsertHelp(rt->right, k , brand, color);

    rt->height = 1 + max(h(rt->left), h(rt->right));
    int balance = GetBalance(rt);

    if((balance < -1) && (k >= rt->right->key)) return LeftRotate(rt);
    if((balance >  1) && (k <  rt->left->key))  return RightRotate(rt);
    if((balance >  1) && (k >= rt->left->key)) {
        rt->left = LeftRotate(rt->left);
        return RightRotate(rt);
    }
    if((balance < -1) && (k < rt->right->key)) {
        rt->right = RightRotate(rt->right);
        return LeftRotate(rt);
    }
    return rt;
}

void Insert(AVL* avl, int k, string brand, string color) {
    avl->root = InsertHelp(avl->root, k, brand, color);
    avl->count++;
}

AVLNode* GetMin(AVLNode* rt) {
    if(rt->left == nullptr) return rt;
    return GetMin(rt->left);
}

AVLNode* DeleteMin(AVLNode* rt) {
    if(rt->left == nullptr) {
        AVLNode* temp = rt->right;
        delete rt;
        return temp;
    }
    rt->left = DeleteMin(rt->left);
    return rt;
}

void PosOrderPrintHelp(AVLNode* rt) {
    if(rt != nullptr) {
        PosOrderPrintHelp(rt->left);
        PosOrderPrintHelp(rt->right);
        cout << rt->brand << "_" << rt->color << endl;
    }
}

void PosOrderPrint(AVL* avl) {
    cout << "--------POS-ORDER--------" << endl;
    PosOrderPrintHelp(avl->root);
    cout << endl << "-------------------------" << endl << endl;
}

void PosOrderDelete(AVLNode* rt) {
    if(rt != nullptr) {
        PosOrderDelete(rt->left);
        PosOrderDelete(rt->right);
        delete rt;
    }
}

void DeleteAVL(AVL* avl) {
    PosOrderDelete(avl->root);
    delete avl;
}

int main() {
    AVL *avl = CreateAVL();

    int n; cin >> n;
    while(n--) {
        Heap* heap = HeapInit(MAX_SIZE);
        string brand, color; cin >> brand;
        
        int rate, i=0;
        while((cin >> rate) && (rate != -1)) {
            i++;
            heap->H[i].rate = rate; 
        } 
        for (int j = 1; j <= i; j++) {
            heap->H[j].brand = brand;
            cin >> heap->H[j].color;
        }
        heap->size = i;
        
        HeapSort(heap, 1);
        Insert(avl, heap->H[heap->size].rate, heap->H[heap->size].brand, heap->H[heap->size].color);

        DeleteHeap(heap);
    }

    PosOrderPrint(avl);

    DeleteAVL(avl);
    return 0;
}
// g++ AVL+Heap.cpp -o a && ./a < input.in


/*
Uma indústria automobilística deseja armazenar as informações das cores mais requisitadas por modelo. Você como programador sabe que uma forma eficiente de guardar e acessar essas informações é usar uma AVL. O seu objetivo será mostrar, em pós-ordem, os modelos e as cores correspondentes que foram inseridas na AVL. Só será inserido na AVL a cor mais produzida por modelo.
Input Specification 

Será dado, inicialmente, o número n de modelos a serem analisados. Após isso, será fornecido o modelo , um vetor com as quantidades de carros vendidos desse modelo (o último valor do vetor sempre será -1 e só servirá para indicar o final do input) e um vetor com as cores correspondentes (na mesma ordem do vetor de quantidades). 

Output Specification 

Printar, em pós-ordem, os modelos e as respectivas cores que foram inseridas na AVL.
Obs: não terá números repetidos na AVL. 

Sample Input 

5
Audi
18 40 37 73 20 61 -1
amarela vermelha cinza prata azul verde 
Mercedes
14 30 39 92 12 -1
laranja cinza azul dourada preta
BMW
15 83 74 63 -1
vermelha preta verde cinza 
Volvo
60 7 11 -1
branco preto cinza
Ferrari
30 -1
vermelha 

Sample Output 

Ferrari vermelha
Audi prata
Volvo branco
Mercedes dourada
BMW preta
*/