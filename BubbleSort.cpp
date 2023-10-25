#include <iostream>
using namespace std;

void Swap(int arr[], int i, int j) {
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

// visualizacao grafica em https://www.programiz.com/dsa/bubble-sort

void BubbleSort(int arr[], int n) {

    for (int i = 0; i < (n-1); i++) { // passa por todos os elementos menos o ultimo, ele ja eh abrangido pelo j+1
        for (int j = 0; j < ((n-1)-i); j++) { // cada vez que i eh incrementado, o for de dentro precisa checar menos os elementos de maiores index
            
            if(arr[j] > arr[j+1]) Swap(arr, j, j+1);
        }
    }
}

int main() {

    int arr[] = {89, 45, 68, 90, 29, 34, 17};
    int n = sizeof(arr)/sizeof(int);
    //cout << "n = " << n << endl;

    BubbleSort(arr, n);

    for(int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // expected output: 17 29 34 45 68 89 90
    return 0;
}