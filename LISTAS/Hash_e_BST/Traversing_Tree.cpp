#include <iostream>
using namespace std;

// TREEVERSE - Traversing Tree - SOLVED
// https://www.spoj.com/problems/TREEVERSE/

typedef struct bstnode {
    int key;
    bstnode *left, *right; 
} BSTNode;

typedef struct {
    BSTNode *root;
    int count;
} BST;

BSTNode* CreateBSTNode(int k) {
    BSTNode* n = new BSTNode;
    n->key = k;
    n->left = n->right = nullptr;
    return n;
} 

BST* CreateBST() {
    BST* bst = new BST;
    bst->count = 0;
    bst->root = nullptr;
    return bst; 
}

BSTNode* InsertHelp(BSTNode* rt, int k) {
    if(rt == nullptr) return CreateBSTNode(k);
    if(rt->key > k) rt->left = InsertHelp(rt->left, k);
    else rt->right = InsertHelp(rt->right, k);
    return rt;
}

void Insert(BST* bst, int k) {
    bst->root = InsertHelp(bst->root, k);
    bst->count++;
}

void PosOrderDelete(BSTNode* rt) {
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

void InOrderPrintHelp(BSTNode* rt) {
    if(rt != nullptr) {
        InOrderPrintHelp(rt->left);
        cout << " " << rt->key;
        InOrderPrintHelp(rt->right);
    }
}

void InOrderPrint(BST* bst) {
    cout << "In order  :";
    InOrderPrintHelp(bst->root);
    cout << endl;
}

void PreOrderPrintHelp(BSTNode* rt) {
    if(rt != nullptr) {
        cout << " " << rt->key;
        PreOrderPrintHelp(rt->left);
        PreOrderPrintHelp(rt->right);
    }
}

void PreOrderPrint(BST* bst) {
    cout << "Pre order :";
    PreOrderPrintHelp(bst->root);
    cout << endl;
}

void PosOrderPrintHelp(BSTNode* rt) {
    if(rt != nullptr) {
        PosOrderPrintHelp(rt->left);
        PosOrderPrintHelp(rt->right);
        cout << " " << rt->key;
    }
}

void PosOrderPrint(BST* bst) {
    cout << "Post order:";
    PosOrderPrintHelp(bst->root);
    cout << endl;
}

int main () {
    BST* bst = CreateBST();
    int n, curr; 
    cin >> n;

    while(n--) {
        cin >> curr;
        Insert(bst, curr);
    }

    PreOrderPrint(bst);
    InOrderPrint(bst);
    PosOrderPrint(bst);

    DeleteBST(bst);
    return 0;
}
// g++ Traversing_Tree.cpp -o TT 
// g++ Traversing_Tree.cpp -o TT && ./TT < input.in