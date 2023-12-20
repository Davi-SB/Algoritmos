#include <iostream>
#include <string>
using namespace std;

// https://www.spoj.com/problems/HASHIT/

#define endl '\n'
#define TABLE_SIZE 101

typedef struct {
    pair<int, string> data;
    bool occupied; // se ocupado, nao inserir (insert). diz se o valor eh relevante
} TableElement;

typedef struct {
    TableElement table[TABLE_SIZE];
    int maxSize;
    int count;
} HashTable;

void PairSwap(pair<int, string> arr[], int i, int j) {
    pair<int, string> temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int Partition(pair<int, string> arr[], int left, int right) {
    int pivot = arr[left].first;
    int i = left, j = right+1;
    do {
        do { i++; } while((arr[i].first < pivot) && (i < right));
        do { j--; } while(arr[j].first > pivot);

        PairSwap(arr, i, j);
    } while(i < j);

    PairSwap(arr, i, j);
    PairSwap(arr, left, j);
    return j;
}

void QuickSort(pair<int, string> arr[], int left, int right) {
    if(left < right) {
        int s = Partition(arr, left, right);

        QuickSort(arr, left, s-1);
        QuickSort(arr, s+1, right);
    }
}

HashTable* InitHashTable() {
    HashTable* ht = new HashTable;
    for (int i = 0; i < TABLE_SIZE; ++i) { // inicializa todos os occupied como false
        ht->table[i].occupied = false;
    }
    ht->maxSize = TABLE_SIZE;
    ht->count = 0;
    return ht;
}

int HashFunction(string element) {
    int sum=0;
    for (int i = 0; i < static_cast<int>(element.size()); i++) {
        sum += (element[i] * (i+1));
    }
    return abs(sum*19) % TABLE_SIZE;
}

int Find(HashTable* ht, string element, int index) { // retorna o indice da key no array de table se encontrar. se nao, retorna -1
    int j=1, saved = index;
    while(ht->table[index].occupied && (ht->table[index].data.second != element) && (j < 20)) {
        index = ((saved+(j*j)+(23*j)) % TABLE_SIZE);
        j++;
    }

    if(ht->table[index].occupied && (ht->table[index].data.second == element)) return index; // para o element ter sido mesmo achado, saiu do while unicamente por causa da condicao (!= element)
    return -1;
}

void Insert(HashTable* ht, string element) {
    int index = HashFunction(element);
    int saved = index;

    if((ht->count >= ht->maxSize) || (Find(ht, element, index) != -1)) return; // checa se nao esta cheio antes de inserir e se o elemento nao eh repetido

    int j=1;

    while(ht->table[index].occupied && (j < 20)) {
        index = ((saved+(j*j)+(23*j)) % TABLE_SIZE);
        j++;
    }

    ht->table[index].data.first = index;
    ht->table[index].data.second = element;
    ht->table[index].occupied = true;
    ht->count++;
}

void Remove(HashTable* ht, string element) {
    int index = Find(ht, element, HashFunction(element));
    if(index == -1) return; 

    ht->table[index].occupied = false; // lazy deletion!!
    ht->count--;
}

pair<int, string>* GetData(HashTable* ht) {
    pair<int, string>* data = new pair<int, string>[ht->count];
    int j=0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if(ht->table[i].occupied) {
            data[j] = ht->table[i].data;
            j++;
        } 
    }
    return data;
}

void PrintData(pair<int, string> data[], int size) {
    for (int i = 0; i < size; i++) {
        cout << data[i].first << ":" << data[i].second << endl;
    } 
}

int main() {
    string act, currKey;
    int nTests, nOperations; 

    cin >> nTests;
    while(nTests--) { 
        HashTable* ht = InitHashTable();
        
        cin >> nOperations; cin.ignore();
        while(nOperations--) {
            getline(cin, act, ':');
            getline(cin, currKey, '\n');
            if(act == "ADD") {
                Insert(ht, currKey);
            }
            else { // DEL
                Remove(ht, currKey);
            }        
        }

        cout << ht->count << endl; // first line
        pair<int, string> *data;
        data = GetData(ht);
        QuickSort(data, 0, (ht->count)-1);
        PrintData(data, ht->count); // second line

        act.clear();
        delete ht;  
        //cout << endl; //sera????????  
    }

    return 0;
}
// g++ Hash_it.cpp -o HIT
// g++ Hash_it.cpp -o HIT && ./HIT < input.in

