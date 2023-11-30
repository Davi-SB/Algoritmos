#include <iostream>
using namespace std;

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
    bool occupied; // se ocupado, nao inserir (insert). diz se o valor eh relevante
    bool unsealed; // se deslacrado, continuar procurando. uma vez deslacrado, nunca mais volta a ser como era antes. 
} TableElement;

typedef struct {
    TableElement table[TABLE_SIZE];
    int maxSize;
    int count;
} HashTable;

HashTable* InitHashTable() {
    HashTable* ht = new HashTable;
    
    for (int i = 0; i < TABLE_SIZE; ++i) { // inicializa todos os occupied como false
        ht->table[i].occupied = false;
        ht->table[i].unsealed = false;
    }

    ht->maxSize = TABLE_SIZE;
    ht->count = 0;
    return ht;
}

int HashFunction(int key) { // nao muito eficiente. usada apenas para fins de estudo
    return key % TABLE_SIZE;
}

int Find(HashTable* ht, int key) {
    int index = HashFunction(key);
    if (ht->table[index].key == key && ht->table[index].occupied) return index;

    int newIndex = (index + 1) % ht->maxSize;

    while (newIndex != index) {
        if (ht->table[newIndex].key == key && ht->table[newIndex].occupied) return newIndex;
        newIndex = (newIndex + 1) % ht->maxSize;
    }
    return -1; // retorna -1 se a chave nao for encontrada na tabela
}

void Insert_linearProbing(HashTable* ht, int key, int value) {
    if ((ht->count >= ht->maxSize) || (Find(ht, key) != -1)) return; // checa se esta cheio antes de inserir ou se o elemento ja existe

    int index = HashFunction(key);

    if (ht->table[index].occupied) {
        int newIndex = (index + 1) % ht->maxSize;

        while (ht->table[newIndex].occupied) {
            newIndex = (newIndex + 1) % ht->maxSize; // itera ate encontrar um slot vazio
        }
        index = newIndex;
    }

    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].occupied = ht->table[index].unsealed = true;
    ht->count++;
}

int RemoveMelhorado(HashTable* ht, int key) {
    int index = Find(ht, key);
    if(index == -1) { cout << "RemoveMelhorado nao encontrou elemento para remover" << endl; return -1; }

    ht->table[index].occupied = false; // lazy deletion!!
    ht->count--;
    return ht->table[index].value;
}

int main() {
    HashTable* ht = InitHashTable();

    Insert_linearProbing(ht, 5, 100);
    Insert_linearProbing(ht, 15, 200);
    Insert_linearProbing(ht, 25, 300);

    cout << "HF 5: " << HashFunction(5) << endl;
    cout << "HF 15: " << HashFunction(15) << endl;
    cout << "HF 25: " << HashFunction(25) << endl;

    cout << "index do 5: " << Find(ht, 5) << endl;
    cout << "index do 15: " << Find(ht, 15) << endl;
    cout << "index do 25: " << Find(ht, 25) << endl;

    if (Find(ht, 8) != -1) cout << "Key 8 found" << endl;
    else cout << "Key 8 not found" << endl; // Deve imprimir "Key 8 not found"

    if (Find(ht, 5) != -1) cout << "Key 5 found" << endl; // Deve imprimir "Key 5 found"
    else cout << "Key 5 not found" << endl; 

    RemoveMelhorado(ht, 5);

    if (Find(ht, 5) != -1) cout << "Key 5 found" << endl;
    else cout << "Key 5 not found" << endl; // Deve imprimir "Key 5 not found"

    if (Find(ht, 25) != -1) cout << "Key 25 found" << endl; // Deve imprimir "Key 25 found"
    else cout << "Key 25 not found" << endl; 

    RemoveMelhorado(ht, 25);

    if (Find(ht, 25) != -1) cout << "Key 25 found" << endl;
    else cout << "Key 25 not found" << endl; // Deve imprimir "Key 25 not found"

    delete ht;
    return 0;
}