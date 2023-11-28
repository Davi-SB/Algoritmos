#include<iostream>
#include<utility>
using namespace std;
#define KEY_TYPE int
#define E int
#define TAM 8



typedef struct{
    int m; // tamanho da hash table, max size
    int count; // n de elementos no dicionario
    pair<KEY_TYPE, E> H[TAM]; // 
    int *perm; // [TAM-1]
} Dictionary;

Dictionary* CreateDict(int size) {
    Dictionary* d = new Dictionary;
    d->m = size;
    d->count = 0;
    int tempPerm[] = {2,6,7,3,1,4,5}; // vetor permutacao eh dado pela questao
    d->perm = tempPerm;
    return d;
}

int HashFunction(KEY_TYPE k) { //////////////////////////////////////////////////////
    return (k % TAM);
}

int find(Dictionary* d, KEY_TYPE k) {
    int i = HashFunction(k);
    whi
}

void Insert(Dictionary* d, KEY_TYPE k, E e) {
    if((d->count < d->m) && find(d, k) == -1) {
        KEY_TYPE pos = HashFunction(k);
        //
    }
}

int main() {



    return 0;
}