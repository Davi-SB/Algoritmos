#include <iostream>
#include <string>
using namespace std;

int main() { 
    string str;

    cin >> str; // le a string ate um espaco, enter ou tab
    cout<< str << endl; // exibe a string
    
    getline(cin, str); // le a linha toda a linha, inclui espacos
    cout << str <<endl;
    
    cout << str.length() << endl; // str.size() tambem funciona

    str = "100";

    int qtd;
    qtd = stoi(str); // converte a string "100" para o inteiro 100
    cout << qtd << endl;
    
    str = "Gustavo";
    cout << str;

    string strConcat = str + " Carvalho"; // + concatena
    cout << strConcat << endl;

    string nome1 = "Artur", nome2 = "Bianca";
    
    if(nome1 > nome2) { // comparadores > e < fazem a comparacao lexicografica (ASCII) letra por letra ate que haja uma diferente e compara o valor dessas
        cout << "True" << endl;
    }
    else cout << "False" << endl;
    
    str.clear();

    return 0;
}
 