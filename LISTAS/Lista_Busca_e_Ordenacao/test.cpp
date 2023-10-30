#include <iostream>

using namespace std;

int main() {
    cout << "Digite uma sequência de números inteiros separados por espaços: ";

    int num;
    while (cin >> num) {
        cout << "Você digitou: " << num << endl;
    }

    return 0;
}
