#include <iostream>
#include <cmath>
using namespace std;

// B - Hacking the random number generator

int main() {
    int n, k, cont=0; 
    int i, j;
    cin >> n;
    cin >> k;
    cin.ignore(); // '\n'
    int arr[n]; // declarar o array apos ja ter o valor de n
    for (i = 0; i < n; i++) {
        cin >> arr[i];
        
        for (j = (i-1); j >= 0; j--) {
            if(abs(arr[i]-arr[j]) == k) {
                cont++;
            }
        }
    }
    cout << cont;
    return 0;
}