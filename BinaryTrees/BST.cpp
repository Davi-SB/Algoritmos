#include <iostream>
using namespace std;
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
    if(rt == nullptr) return '\0';
    if(rt->key > k) return FindHelp(rt->left, k);
    else if(rt->key == k) return rt->element;
    else return FindHelp(rt->right, k);
}

E Find(BST* bst, int k) {
    return FindHelp(bst->root, k); 
}

BSTNode* InsertHelp(BSTNode* rt, int k, E e) {
    if(rt == nullptr) return CreateBSTNode(k, e);
    if(rt->key > k) rt->left = InsertHelp(rt->left, k, e);
    else rt->right = InsertHelp(rt->right, k ,e);
    return rt;
}

void Insert(BST* bst, int k, E e) {
    bst->root = InsertHelp(bst->root, k, e);
    bst->count++;
}

BSTNode* GetMin(BSTNode* rt) {
    if(rt->left == nullptr) return rt;
    return GetMin(rt->left);
}

BSTNode* DeleteMin(BSTNode* rt) {
    if(rt->left == nullptr) return rt->right;
    rt->left = DeleteMin(rt->left);
    return rt;
}

BSTNode* DeleteMinGPT(BSTNode* rt) {
    if(rt->left == nullptr) {
        BSTNode* temp = rt->right;
        delete rt; // Deleting the node to free memory
        return temp;
    }
    rt->left = DeleteMin(rt->left);
    return rt;
}


BSTNode* RemoveHelp(BSTNode* rt, int k) {
    if(rt == nullptr) return NULL;
    if(rt->key > k) rt->left = RemoveHelp(rt->left, k);
    else if(rt->key < k) rt->right = RemoveHelp(rt->right, k);
    else {
        if(rt->left == nullptr) { 
            BSTNode* temp = rt->right;
            delete rt;
            return temp;
        }
        else if(rt->right == nullptr) {
            BSTNode* temp = rt->left;
            delete rt;
            return temp;
        }
        else { // caso de duas subarvores nao vazias
            BSTNode *temp = GetMin(rt->right);
            rt->element = temp->element;
            rt->key = temp->key;
            rt->right = DeleteMin(rt->right);
        }
    }
    return rt;
}

E remove(BST* bst, int k) {
    E temp = FindHelp(bst->root, k);
    if(temp != '\0') {
        bst->root = RemoveHelp(bst->root, k);
        bst->count--;
    }
    return temp;
}

E PosOrderDelete(BSTNode* rt) {
    if(rt != nullptr) {
        PosOrderDelete(rt->left);
        PosOrderDelete(rt->right);
        delete rt;
    }
}

void DeleteBST(BST* bst) {
    PosOrderDelete(bst->root);
    delete bst;
}

int main () {



    return 0;
}