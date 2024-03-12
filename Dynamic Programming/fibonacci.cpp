#include <iostream>
using namespace std;

int fibonacci(int n) {
    int a = 0, b = 1;
    if (n == 0 || n == 1) return n;

    for (int i = 2; i <= n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    int n;
    cout << "Digite o valor de n: ";
    cin >> n;
    cout << "O " << n << "-esimo elemento da sequência de Fibonacci eh: " << fibonacci(n) << endl;
    return 0;
}
