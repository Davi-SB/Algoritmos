#include <iostream>
using namespace std;
#define E char

typedef struct avlnode {
    int key, height;
    E element;
    avlnode *left, *right; 
} AVLNode;

typedef struct {
    AVLNode *root;
    int count;
} AVL;

AVLNode* CreateAVLNode(int k, E e) {
    AVLNode* n = new AVLNode;
    n->key = k;
    n->height = -1;
    n->element = e;
    n->left = n->right = nullptr;
    return n;
} 

AVL* CreateAVL() {
    AVL* avl = new AVL;
    avl->count = 0;
    avl->root = nullptr;
    return avl; 
}

E FindHelp(AVLNode* rt, int k) {
    if(rt == nullptr) return '\0';
    if(rt->key > k) return FindHelp(rt->left, k);
    else if(rt->key == k) return rt->element;
    else return FindHelp(rt->right, k);
}

E Find(AVL* avl, int k) {
    return FindHelp(avl->root, k); 
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
    return l; // nova raiz da subarvore em questao
}

AVLNode* LeftRotate(AVLNode* rt) {
    AVLNode *r  = rt->right;
    AVLNode *rl = r->left;
    r->left  = rt;
    rt->right = rl;
    rt->height = 1 + max(h(rt->left), h(rt->right));
    r->height =  1 + max(h( r->left), h( r->right));
    return r; // nova raiz da subarvore em questao
}

int GetBalance(AVLNode* rt) {
    if(rt == NULL) return 0;
    return (h(rt->left) - h(rt->right)); // balance factor
}

AVLNode* InsertHelp(AVLNode* rt, int k, E e) {
    if(rt == nullptr) return CreateAVLNode(k, e);
    if(rt->key > k) rt->left = InsertHelp(rt->left, k, e);
    else rt->right = InsertHelp(rt->right, k ,e);

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

void Insert(AVL* avl, int k, E e) {
    avl->root = InsertHelp(avl->root, k, e);
    avl->count++;
}

AVLNode* GetMin(AVLNode* rt) {
    if(rt->left == nullptr) return rt;
    return GetMin(rt->left);
}

AVLNode* DeleteMin(AVLNode* rt) {
    if(rt->left == nullptr) {
        AVLNode* temp = rt->right;
        delete rt; // Deleting the node to free memory
        return temp;
    }
    rt->left = DeleteMin(rt->left);
    return rt;
}

void InOrderPrintHelp(AVLNode* rt) {
    if(rt != nullptr) {
        InOrderPrintHelp(rt->left);
        cout << "<" << rt->key << ", " << rt->element << ">  ";
        InOrderPrintHelp(rt->right);
    }
}

void InOrderPrint(AVL* avl) {
    cout << "--------IN-ORDER--------" << endl;
    InOrderPrintHelp(avl->root);
    cout << endl << "------------------------" << endl << endl;
}

void PreOrderPrintHelp(AVLNode* rt) {
    if(rt != nullptr) {
        cout << "<" << rt->key << ", " << rt->element << ">  ";
        PreOrderPrintHelp(rt->left);
        PreOrderPrintHelp(rt->right);
    }
}

void PreOrderPrint(AVL* avl) {
    cout << "--------PRE-ORDER--------" << endl;
    PreOrderPrintHelp(avl->root);
    cout << endl << "-------------------------" << endl << endl;
}

void PosOrderPrintHelp(AVLNode* rt) {
    if(rt != nullptr) {
        PosOrderPrintHelp(rt->left);
        PosOrderPrintHelp(rt->right);
        cout << "<" << rt->key << ", " << rt->element << ">  ";
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

int main () {
    AVL* avl = CreateAVL();

    Insert(avl, 5, '_');   
    Insert(avl, 3, 't');
    Insert(avl, 7, 'e');
    Insert(avl, 2, 's');
    Insert(avl, 4, 't');
    Insert(avl, 6, 'e');
    Insert(avl, 1, '_');

    PreOrderPrint(avl);
    InOrderPrint(avl);
    PosOrderPrint(avl);

    DeleteAVL(avl);
    return 0;
}

/*
int main () {
    AVL* avl = CreateAVL();

    Insert(avl, 4, ' ');   
    Insert(avl, 6, ' ');
    Insert(avl, 8, ' ');
    Insert(avl, 3, ' ');
    Insert(avl, 2, ' ');
    Insert(avl, 5, ' ');

    PreOrderPrint(avl);
    InOrderPrint(avl);
    PosOrderPrint(avl);

    DeleteAVL(avl);
    return 0;
}
*/
