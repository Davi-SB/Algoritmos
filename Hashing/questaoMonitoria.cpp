#include <iostream>
using namespace std;

#define TABLE_SIZE 7
#define endl '\n'

typedef struct {
    string cpf;
    string name;
    bool occupied; // se ocupado, nao inserir (insert). diz se o valor eh relevante
    bool unsealed; // se deslacrado, continuar procurando. uma vez deslacrado, nunca mais volta a ser como era antes. 
} TableElement;

typedef struct {
    TableElement table[TABLE_SIZE];
    int perm[TABLE_SIZE-1];
    int maxSize;
    int count;
} HashTable;

HashTable* InitHashTable() {
    HashTable* ht = new HashTable;
    
    for (int i = 0; i < TABLE_SIZE; ++i) { // inicializa todos os occupied como false
        ht->table[i].occupied = false;
        ht->table[i].unsealed = false;
    }
    
    int tempPerm[] = {10,5,7,6,2,4};
    for (int i = 0; i < (TABLE_SIZE-1); i++) { // preenche o vetor perm
        ht->perm[i] = tempPerm[i];    
    }

    ht->maxSize = TABLE_SIZE;
    ht->count = 0;
    return ht;
}

int HashFunction(string cpf) {
    int sum=0;
    for (int i = 0; i < static_cast<int>(cpf.size()); i++) {
        sum += (cpf[i] - '0');
    }
    return sum % TABLE_SIZE;
}

string Find(HashTable* ht, string cpf) { // retorna o indice da cpf no array de table se encontrar. se nao, retorna -1
    int index = HashFunction(cpf);
    if (ht->table[index].cpf == cpf && ht->table[index].occupied) {
        cout << ht->table[index].name << " " << index << endl;
        return ht->table[index].name;
    }

    int i = 0;
    int newIndex=0;

    do {
        i++;
        int offset = ht->perm[i-1];
        newIndex = (index + offset) % ht->maxSize;
        //
        if(!ht->table[newIndex].unsealed) {
            cout << "-1" << endl;
            return "-1"; // se um indice NAO usado foi encontrado, ja pode parar a busca
        }
        //
        if ((ht->table[newIndex].cpf == cpf) && (ht->table[newIndex].occupied)) {
            cout << ht->table[newIndex].name << " " << newIndex << endl;
            return ht->table[newIndex].name;
        }
    } while (i < (TABLE_SIZE-1));

    cout << "-1" << endl;
    return "-1";
}

string FindCheck(HashTable* ht, string cpf) { // retorna o indice da cpf no array de table se encontrar. se nao, retorna -1
    int index = HashFunction(cpf);
    if (ht->table[index].cpf == cpf && ht->table[index].occupied) {
        return ht->table[index].name;
    }

    int i = 0;
    int newIndex;

    do {
        i++;
        int offset = ht->perm[i-1];
        newIndex = (index + offset) % ht->maxSize;
        //
        if(!ht->table[newIndex].unsealed) {
            return "-1"; // se um indice NAO usado foi encontrado, ja pode parar a busca
        }
        //
        if ((ht->table[newIndex].cpf == cpf) && (ht->table[newIndex].occupied)) {
            return ht->table[newIndex].name;
        }
    } while (i < (TABLE_SIZE-1));

    return "-1";
}

void Insert_randomProbing(HashTable* ht, string cpf, string name) {
    if((ht->count >= ht->maxSize) || (FindCheck(ht, cpf) != "-1")) return; // checa se nao esta cheio antes de inserir e se o elemento nao eh repetido

    int index = HashFunction(cpf);

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

    ht->table[index].cpf = cpf;
    ht->table[index].name = name;
    ht->table[index].occupied = ht->table[index].unsealed = true;
    ht->count++;
}

int main() {
    HashTable* ht = InitHashTable();
    string acao = "", nomeCliente = "", CPFprocurado = "";

    for (int i = 0; i < 18; i++) {
        cin >> acao;
        if(acao == "add") {
            cin >> nomeCliente;
            cin >> CPFprocurado;
            Insert_randomProbing(ht, CPFprocurado, nomeCliente);
        }
        else { // acao == "find"
            cin >> CPFprocurado;
            Find(ht, CPFprocurado);
        }
    }
    
    delete ht;
    return 0;
}
// g++ questaoMonitoria.cpp -o QM
// g++ questaoMonitoria.cpp -o QM && ./QM < input.txt