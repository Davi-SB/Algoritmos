#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
using namespace std;

#define TABLE_SIZE 10

typedef struct {
    int key;
    int value;
    bool occupied;
} HashEntry;

typedef struct {
    HashEntry entries[TABLE_SIZE];
    int perm[TABLE_SIZE-1];
    int maxSize;
    int count;
} HashTable;

HashTable* initHashTable() {
    HashTable* ht = new HashTable;
    
    for (int i = 0; i < TABLE_SIZE; ++i) { // inicializa todos os occupied como false
        ht->entries[i].occupied = false;
    }
    
    int tempPerm[] = {2,6,7,3,1,4,5,9,8};
    for (int i = 0; i < (TABLE_SIZE-1); i++) { // preenche o vetor perm
        ht->perm[i] = tempPerm[i];    
    }

    ht->maxSize = TABLE_SIZE;
    ht->count = 0;
    return ht;
}

int HashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert_linearProbing(HashTable* ht, int key, int value) { // checar se nao esta cheio antes de inserir e se o elemento nao eh repetido
    if(ht->count >= ht->maxSize || find(ht, key)) return; // checar se nao esta cheio antes de inserir e se o elemento nao eh repetido

    int index = HashFunction(key);

    while (ht->entries[index].occupied) { // verifica se ja pode inserir
        // Linear probing: move to the next slot
        index = (index + 1) % TABLE_SIZE;
    }

    ht->entries[index].key = key;
    ht->entries[index].value = value;
    ht->entries[index].occupied = true;
    ht->count++;
}

/*
void insert(HashTable* ht, int key, int value) {
    unsigned int index = HashFunction(key);

    while (ht->entries[index].occupied) {
        // Linear probing: move to the next slot
        index = (index + 1) % TABLE_SIZE;
    }

    ht->entries[index].key = key;
    ht->entries[index].value = value;
    ht->entries[index].occupied = true;
}
*/

bool find(HashTable* ht, int key, int* value) {
    unsigned int index = HashFunction(key);
    unsigned int originalIndex = index;

    while (ht->entries[index].occupied) {
        if (ht->entries[index].key == key) {
            *value = ht->entries[index].value;
            return true;
        }
        // Linear probing: move to the next slot
        index = (index + 1) % TABLE_SIZE;

        // If we've checked all slots and looped back to the start, break to avoid infinite loop
        if (index == originalIndex) {
            break;
        }
    }

    return false;
}

int main() {
    HashTable *myHashTable = initHashTable();

    insert(&myHashTable, 5, 100);
    insert(&myHashTable, 15, 200);
    insert(&myHashTable, 25, 300);

    int val;
    if (find(&myHashTable, 15, &val)) {
        printf("Value found: %d\n", val);
    } else {
        printf("Value not found.\n");
    }

    if (find(&myHashTable, 8, &val)) {
        printf("Value found: %d\n", val);
    } else {
        printf("Value not found.\n");
    }

    return 0;
}
