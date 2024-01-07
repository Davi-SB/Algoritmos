#include <iostream>
#include <limits.h>
using namespace std;
#define endl '\n'

typedef struct avlnode {
    int key, height, leftChildren, rightChildren;
    avlnode *left, *right; 
} AVLNode;

typedef struct {
    AVLNode *root;
    int count;
} AVL;

AVLNode* CreateAVLNode(int k) {
    AVLNode* n = new AVLNode;
    n->key = k;
    n->height = -1;
    n->leftChildren = n->rightChildren = 0;
    n->left = n->right = nullptr;
    return n;
} 

AVL* CreateAVL() {
    AVL* avl = new AVL;
    avl->count = 0;
    avl->root = nullptr;
    return avl; 
}

int FindHelp(AVLNode* rt, int k) {
    if(rt == nullptr) return INT_MIN;
    if(rt->key > k) return FindHelp(rt->left, k);
    else if(rt->key == k) return rt->key;
    else return FindHelp(rt->right, k);
}

int Find(AVL* avl, int k) {
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

    rt->leftChildren = (lr != nullptr) ? lr->leftChildren + lr->rightChildren + 1 : 0; // +1 para contar com lr
    // leftChildren de l nao muda

    return l; // nova raiz da subarvore em questao
}

AVLNode* LeftRotate(AVLNode* rt) {
    AVLNode *r  = rt->right;
    AVLNode *rl = r->left;
    r->left  = rt;
    rt->right = rl;
    rt->height = 1 + max(h(rt->left), h(rt->right));
    r->height =  1 + max(h( r->left), h( r->right));

    r->leftChildren++;
    rt->leftChildren = (rl != nullptr) ? rl->leftChildren + rl->rightChildren + 1 : 0;

    return r; // nova raiz da subarvore em questao
}

int GetBalance(AVLNode* rt) {
    if(rt == NULL) return 0;
    return (h(rt->left) - h(rt->right)); // balance factor
}

AVLNode* InsertHelp(AVLNode* rt, int k) {
    if(rt == nullptr) return CreateAVLNode(k);
    if(rt->key > k) {
        rt->left = InsertHelp(rt->left, k);
        rt->leftChildren++;
    }
    else {
        rt->right = InsertHelp(rt->right, k);
        rt->rightChildren++;
    }

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

void Insert(AVL* avl, int k) {
    avl->root = InsertHelp(avl->root, k);
    avl->count++;
}

AVLNode* GetMin(AVLNode* rt) {
    if(rt->left == nullptr) return rt;
    return GetMin(rt->left);
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

int FindIndexHelp(AVLNode* rt, int k) {
    if(rt == nullptr) return -1;

    if(k == rt->key) return rt->leftChildren;
    else if (k < rt->key) return FindIndexHelp(rt->left, k);
    else return (rt->leftChildren + 1) + FindIndexHelp(rt->right, k); // k > rt->key // tudo que esta a esqueda + o proprio node + index na subarvore
}

int FindIndex(AVL* avl, int k) {
    return FindIndexHelp(avl->root, k);
}

int main () {
    AVL* avl = CreateAVL();
    int q, x;
    char act;

    cin >> q;
    while (q--) {
        cin >> act;
        cin >> x;
        if(act == '1') Insert(avl, x);
        else { // act == '2' // search
            int i = FindIndex(avl, x);
            (i == -1) ? cout << "Data tidak ada" : cout << (i+1); cout << endl;
        }
    }

    DeleteAVL(avl);
    return 0;
}
// g++ AVL_Tree.cpp -o AVLT
// g++ AVL_Tree.cpp -o AVLT && ./AVLT < input.in