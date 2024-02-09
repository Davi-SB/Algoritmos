#include <iostream>
using namespace std;
#define endl '\n'

// sentar pra ver!!

int main() {
    
    string str;
    cin >> str; //reads the string until a space, enter or tab
    //erjfj Victor1207
    cout << str << endl;
    
    getline(cin, str); //reads the whole string including space and tab
    cout << str << endl;
    
    cout << str.size() << endl;
    
    cout << str.substr(1, str.size()) << endl;
    
    string str2;
    //o segundo número indica quantos caracteres serão adicionados na substring
    str2 = str.substr(1, str.size()); 
    
    cout << str2 << endl;
    
    int qtd;
    qtd = stoi(str2.substr(6, 9)); //string to int(Victor1207)
    
    cout << qtd << endl;
    
    string str_sum;
    str_sum = str + str2; //concatena
    
    cout << str_sum << endl;
    
    str.clear(); //equivale a free(str)

    return 0;
}