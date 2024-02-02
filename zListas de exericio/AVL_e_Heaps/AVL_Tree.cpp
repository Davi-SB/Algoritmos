#include <iostream>
#include <limits.h>
using namespace std;
#define endl '\n'

// SOLVED - https://www.spoj.com/problems/SDITSAVL/

typedef struct avlnode {
    int key, height, subsize;
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
    n->subsize = 1; // conta com a root da subarvore
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
    rt->subsize = 1 + (rt->left ? rt->left->subsize : 0) + (rt->right ? rt->right->subsize : 0);

    l->height =  1 + max(h( l->left), h( l->right));
    l->subsize = 1 + (l->left ? l->left->subsize : 0) + (l->right ? l->right->subsize : 0);

    return l; 
}

AVLNode* LeftRotate(AVLNode* rt) {
    AVLNode *r  = rt->right;
    AVLNode *rl = r->left;
    r->left  = rt;
    rt->right = rl;

    rt->height = 1 + max(h(rt->left), h(rt->right));
    rt->subsize = 1 + (rt->left ? rt->left->subsize : 0) + (rt->right ? rt->right->subsize : 0);

    r->height =  1 + max(h( r->left), h( r->right));
    r->subsize = 1 + (r->left ? r->left->subsize : 0) + (r->right ? r->right->subsize : 0);

    return r; 
}

int GetBalance(AVLNode* rt) {
    if(rt == nullptr) return 0;
    return (h(rt->left) - h(rt->right)); // balance factor
}

AVLNode* InsertHelp(AVLNode* rt, int k) {
    if(rt == nullptr) return CreateAVLNode(k);
    if(rt->key > k) rt->left = InsertHelp(rt->left, k);
    else rt->right = InsertHelp(rt->right, k);

    rt->height = 1 + max(h(rt->left), h(rt->right));
    rt->subsize = 1 + (rt->left ? rt->left->subsize : 0) + (rt->right ? rt->right->subsize : 0);
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

    if(rt->key <= k) {
        if(rt->left == nullptr) return (1 + FindIndexHelp(rt->right, k));
        else return (1 + rt->left->subsize + FindIndexHelp(rt->right, k)); 
    }
    else return FindIndexHelp(rt->left, k);
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
            if(Find(avl, x) != INT_MIN) { // achou
            cout << (1 + FindIndex(avl, x)) << endl;
            }
            else cout << "Data tidak ada" << endl;
        }
    }
    DeleteAVL(avl);
    return 0;
}
// g++ AVL_Tree_copy.cpp -o AVLT
// g++ AVL_Tree_copy.cpp -o AVLT && ./AVLT < input.in