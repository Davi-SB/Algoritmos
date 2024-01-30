#include <iostream>
using namespace std;

template<typename T>
class Node {
private:
    int key;
    T element;
    Node<T> *left, *right;
public:
    Node(int key, T element) {
        this->key = key;
        this->element = element;
        this->left = this->right = nullptr;
    }
    Node(int key) {
        this->key = this->element = key; // key se torna o elemento
        this->left = this->right = nullptr;
    }
    ~Node(){}
};

template<typename T>
class BST {
private:
    Node<T> *root;
    int count;

    void posOrderDelete(Node<T> *rt) {
        if(rt != nullptr) {
            posOrderDelete(rt->left);
            posOrderDelete(rt->right);
            delete rt;
        }
    }

    T find(Node<T> *rt, int k) {
        if(rt == nullptr) return '\0';
        if(rt->key > k) return find(rt->left, k);
        else if(rt->key == k) return rt->element;
        else return find(rt->right, k);
    }

public:
    BST() {
        count = 0;
        root = nullptr; 
    }
    ~BST() { PosOrderDelete(root); }

    T find(int key) { return find(root, key); }
};

int main() {
    return 0;
}