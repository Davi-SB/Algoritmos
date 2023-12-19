#include <iostream>
#define E int

typedef struct bstnode {
    int key;
    E element;
    bstnode *left, *right; 
} BSTNode;

typedef struct {
    BSTNode *root;
    int count;
} BST;

BSTNode* CreateBSTNode(int k, E e) {
    BSTNode* n = new BSTNode;
    n->key = k;
    n->element = e;
    n->left = n->right = nullptr;
    return n;
} 

BST* CreateBST() {
    BST* bst = new BST;
    bst->count = 0;
    bst->root = nullptr;
    return bst; 
}

E FindHelp(BSTNode* rt, int k) {
    if(rt == NULL) return NULL;
}

E Find(BST* bst, int k) {
    return FindHelp(bst->root, k); 
}

int main () {



    return 0;
}