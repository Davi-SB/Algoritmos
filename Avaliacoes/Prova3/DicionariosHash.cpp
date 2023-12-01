#include <iostream>
#include <cmath>
using namespace std;

#define endl '\n'

typedef struct {
    int key;
    int value;
    bool occupied; // se ocupado, nao inserir (insert). diz se o valor eh relevante
    bool unsealed; // se deslacrado, continuar procurando. uma vez deslacrado, nunca mais volta a ser como era antes. 
} TableElement;

typedef struct {
    TableElement* table;
    int *perm;
    int maxSize;
    int count;
} HashTable;

int HashFunction(int key, int mod) { 
    int temp = (int) floor((((double) key) / ((double) mod))); 
    return (key - (mod * temp)); 
}

HashTable* HashInit(int m, int perm[]) {
    HashTable* ht = new HashTable;
    
    ht->table = new TableElement[m];
    for (int i = 0; i < m; i++) {
        ht->table[i].occupied = ht->table[i].unsealed = false;
    }

    ht->perm = new int[m-1];
    for (int i = 0; i < (m-1); i++) {
        ht->perm[i] = perm[i];
    }
    
    ht->maxSize = m;
    ht->count = 0;
    return ht;
}

int Find(HashTable* ht, int key) { // retorna o indice da key no array de table se encontrar. se nao, retorna -1
    int index = HashFunction(key, ht->maxSize);
    if (ht->table[index].key == key && ht->table[index].occupied) return index;

    int i = 0;
    int newIndex;

    do {
        i++;
        int offset = ht->perm[i-1];
        newIndex = (index + offset) % ht->maxSize;
        //
        if(!ht->table[newIndex].unsealed) return -1; // se um indice NAO usado foi encontrado, ja pode parar a busca
        //
        if (ht->table[newIndex].key == key && ht->table[newIndex].occupied) return newIndex;
    } while (i < (ht->maxSize - 1));

    return -1;
}

void Find_COUT(HashTable* ht, int key) { // reuso da funcao para printar em vez de retornar
    int index = HashFunction(key, ht->maxSize);
    if (ht->table[index].key == key && ht->table[index].occupied) {
        cout << index << " " << ht->table[index].value << endl;
        return;
    }

    int i = 0;
    int newIndex;

    do {
        i++;
        int offset = ht->perm[i-1];
        newIndex = (index + offset) % ht->maxSize;
        //
        if(!ht->table[newIndex].unsealed) {
            cout << "-1" << endl; // se um indice NAO usado foi encontrado, ja pode parar a busca
            return;
        }
        //
        if (ht->table[newIndex].key == key && ht->table[newIndex].occupied) {
            cout << newIndex << " " << ht->table[newIndex].value << endl;
            return;
        }

    } while (i < (ht->maxSize - 1));

    cout << "-1" << endl;
}

void Insert(HashTable* ht, int key, int value) {
    if((ht->count >= ht->maxSize) || (Find(ht, key) != -1)) return; // checa se nao esta cheio antes de inserir e se o elemento nao eh repetido

    int index = HashFunction(key, ht->maxSize);

    if(ht->table[index].occupied) {
        int i = 0;
        int newIndex;
        do {
            i++;    
            int offset = ht->perm[i-1];
            newIndex = (index + offset) % ht->maxSize;

        } while(ht->table[newIndex].occupied);
        index = newIndex;
    }

    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].occupied = ht->table[index].unsealed = true;
    ht->count++;
}

void HashDelete(HashTable* ht) {
    delete ht->perm;
    ht->perm = nullptr;
    delete ht->table;
    ht->table = nullptr;
    delete ht;
    ht = nullptr;
}

int main() {
    string act = "";
    int currKey, currValue;
    int m; 

    while(cin >> m && m) {
        int perm[m-1];
        for (int i = 0; i < (m-1); i++) {
            cin >> perm[i]; 
        }
        HashTable* ht = HashInit(m, perm);
        
        cin >> m; // m agora eh o numero de operacoes a serem realizadas
        for (int i = 0; i < m; i++) {
            cin >> act;
            if(act == "add") {
                cin >> currKey;
                cin >> currValue;
                Insert(ht, currKey, currValue);
            }
            else { // find
                cin >> currKey;
                Find_COUT(ht, currKey);
            }        
        }
        act.clear();
        HashDelete(ht);    
    }
    return 0;
}

/*
Implemente o tipo abstrato de dados Dicionário utilizando tabelas de dispersão. 
A tabela tem tamanho m e a função hash é a seguinte: h(k) = k − (m * floor(k/m)), 
onde o símbolo / denota a divisão entre números reais e floor denota a função piso. 
A política de resolução de colisões é baseada em pseudo-random probing, conforme 
p(k,i) = perm[i-1], onde perm é o array de permutações.

Input Specification
A entrada consiste em múltiplos casos. Cada caso inicia com um inteiro m >= 0 
(exceto o valor 1). O valor m = 0 representa o final da entrada. Nos casos onde 
m > 1, inicialmente, são apresentados (m-1) números, separados por espaço, referentes 
ao array perm; ou seja, uma permutação dos valores compreendidos entre [1, m-1]. Em 
seguida, tem-se um valor inteiro n > 0, indicando que o caso consiste em realizar n 
operações. As operações possíveis são: inserção (add key value) e busca (find key); 
key e value são números inteiros. Ao tentar inserir uma entrada em um dicionário 
cheio (todas as posições da tabela de dispersão estiverem ocupadas), não faça nada. 
Ao tentar inserir uma entrada indexada por uma chave key já existente no dicionário, 
não faça nada.

Output Specification
Para cada operação de busca (find key), imprima o índice da tabela de dispersão 
no qual se encontra key, além do valor value associado à chave key. Se não existir 
no dicionário um valor indexado por key, imprima -1.

Sample input: 
7
3 4 1 6 2 5
19
add 10 5
add -7 -3
add 3 1
add -5 -2
add 5 2
add -8 -4
find 10
find -7
find 3
find -5
find 5
find -8
find 100
add 100 50
find 100
add 10 6
find 10
add 200 100
find 200
0

Sample output:
3 5
0 -3
6 1
2 -2
5 2
1 -4
-1
4 50
3 5
-1

*/