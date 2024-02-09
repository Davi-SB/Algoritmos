/*#include <iostream>
#include <map>
using namespace std;

int main() {
    // Criando um map onde as chaves sao strings e os valores sao inteiros
    map<string, int> meuMapa;

    // Inserindo elementos no map
    meuMapa["um"] = 1;
    meuMapa["dois"] = 2;
    meuMapa["tres"] = 3;

    // Acessando elementos do map
    cout << "O valor associado a chave 'dois' eh: " << meuMapa["dois"] << endl;
    cout << "O valor associado a chave 'tres' eh: " << meuMapa.at("tres") << endl;
    
    // Iterando sobre todos os elementos do map
    cout << "Todos os elementos do map:" << endl;
    for (pair<string, int> par : meuMapa) {
        cout << par.first << ": " << par.second << endl;
    }

    // Verificando se a chave "dois" esta presente no map
    auto it = meuMapa.find("dois");
    if (it != meuMapa.end()) {
        cout << "A chave 'dois' esta presente no map, e seu valor eh: " << it->second << endl;
    } 
    else {
        cout << "A chave 'dois' nao esta presente no map." << endl;
    }

    // Verificando se a chave "quatro" esta presente no map
    it = meuMapa.find("quatro");
    if (it != meuMapa.end()) {
        cout << "A chave 'quatro' esta presente no map, e seu valor eh: " << it->second << endl;
    } 
    else {
        cout << "A chave 'quatro' nao esta presente no map." << endl;
    }
    return 0;
}*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Exemplo de vetor de pares
    vector<pair<string, int>> vetor = {{"A", 3}, {"B", 1}, {"C", 2}, {"D", 0}, {"E", -1}};

    // Ordenando parcialmente o vetor com base nos inteiros (segundo elemento do par)
    sort(vetor.begin(), vetor.begin() + 3, [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second < b.second;
    });

    // Imprimindo o vetor ordenado parcialmente
    for (const auto& p : vetor) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    return 0;
}

