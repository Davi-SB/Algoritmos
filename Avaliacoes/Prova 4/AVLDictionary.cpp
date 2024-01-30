#include <iostream>
#include <limits.h>
using namespace std;
#define endl '\n'

typedef struct node{
    int key, height;
    node *left, *right;
} AVLNode;

typedef struct AVL {
    int nodeCount;
    AVLNode *root;
} AVL;

AVLNode* CreateNode(int k) {
    AVLNode* n = new AVLNode;
    n->key = k;
    n->height = 0;
    n->left = n->right = nullptr;
    return n;
}

AVL* CreateAVL() {
    AVL* avl = new AVL;
    avl->root = nullptr;
    avl->nodeCount = 0;
    return avl;
}

int h(AVLNode* rt) {
    if(rt == nullptr) return -1;
    return rt->height;
}

int getBalance(AVLNode *rt) {
    if(rt == nullptr) return 0;
    return h(rt->left) - h(rt->right);
}

AVLNode* rightRotate(AVLNode *rt) {
    AVLNode* l = rt->left;
    AVLNode* lr = l->right;

    l->right = rt;
    rt->left = lr;
    rt->height = max(h(rt->left), h(rt->right)) + 1;
    l->height  = max(h( l->left), h( l->right)) + 1;

    return l;
}

AVLNode* leftRotate(AVLNode *rt) {
    AVLNode* r = rt->right;
    AVLNode* rl = r->left;

    r->left = rt;
    rt->right = rl;
    rt->height = max(h(rt->left), h(rt->right)) + 1;
    r->height  = max(h( r->left), h( r->right)) + 1;

    return r;
}

AVLNode* InsertHelp(AVLNode* rt, int key) {
    if(rt == nullptr) return CreateNode(key);
    if(rt->key > key) rt->left = InsertHelp(rt->left, key);
    else rt->right = InsertHelp(rt->right, key);

    rt->height = 1 + max(h(rt->left), h(rt->right));
    int balance = getBalance(rt);

    if((balance < -1) && (key >= rt->right->key)) {
        return leftRotate(rt);
    }
    if((balance >  1) && (key <  rt->left->key)) {
        return rightRotate(rt);
    }
    if((balance >  1) && (key >= rt->left->key)) {
        rt->left = leftRotate(rt->left);
        return rightRotate(rt);
    }
    if((balance < -1) && (key <  rt->right->key)) {
        rt->right = rightRotate(rt->right);
        return leftRotate(rt);
    }
    return rt;
}

void Insert(AVL* avl, int key) {
    avl->root = InsertHelp(avl->root, key);
    avl->nodeCount++;
}

void PreOrderPrint(AVLNode* n) {
    if(n == nullptr) return;
    cout << n->key << endl;
    PreOrderPrint(n->left);
    PreOrderPrint(n->right);
} 

void DeletePosOrder(AVLNode* n) {
    if(n == nullptr) return;
    DeletePosOrder(n->left);
    DeletePosOrder(n->right);
    delete n;
}

void DeleteAvl(AVL* avl) {
    DeletePosOrder(avl->root);
    delete avl;
}

int main() {
    int c; cin >> c;
    while(c--) {
        int n; cin >> n;
        AVL* avl = CreateAVL();        
        while(n--) {
            int curr; cin >> curr;
            Insert(avl, curr);
        }
        PreOrderPrint(avl->root);
        cout << "END" << endl;
        DeleteAvl(avl); // pos order delete
    }
    return 0;
}
// g++ EP.cpp -o EP && ./EP < input.in