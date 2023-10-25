#include <iostream>
using namespace std;

void Swap(int arr[], int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void SelectionSort(int arr[], int n) {

    int min;

    for (int i = 0; i < (n-1); i++) { // passa uma vez por todos mas nao pelo ultimo, quando chega la, ja nao eh necessario mudar nem checar nada

        min = i; // supoe-se que o valor minimo da parte que estamos analizando esta no primeiro item

        for (int j = (i+1); j < n; j++) { // comeca no logo apos nosso i atual e passa por todos
            if(arr[j] < arr[min]) min = j; // acha o min de verdade
        }

        Swap(arr, i, min);
    }

}

int main() {

    int arr[] = {89, 45, 68, 90, 29, 34, 17};
    int n = sizeof(arr)/sizeof(int);
    //cout << "n = " << n << endl;

    SelectionSort(arr, n);

    for(int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // expected output: 17 29 34 45 68 89 90
    return 0;
}