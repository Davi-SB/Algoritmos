#include <iostream>
using namespace std;

void InsertionSort(int arr[], int n) {

    int j, nCheck;

    for (int i = 1; i < n; i++) { // i comeca em 1!!! isso pois o subarray antes dele (somente arr[0]) ja esta ordenado
        
        j = i-1; // a[j] sempre comeca sendo o elemento imediatamente antes ao a[i]
        nCheck = arr[i]; // nCheck eh o numero que esta sendo checado, o que estamos procurando a posicao certa para ser inserido no array

        while ((j>=0) && (arr[j] > nCheck)) { // j>=0 --> roda ate que chegue no ultimo elemento do array // arr[j] > nCheck --> roda enquanto os elementos subarray ordenado forem maiores que o que estamos procurando a posicao
            arr[j+1] = arr[j]; // avanca o elemento checado em uma posicao do array. o arr[i] original acaba perdido, por isso a importancia da variavel nCheck
            j--;
        }
        
        arr[j+1] = nCheck; // Quando achamos um numero menor ou <= a ele (!>), o lugar de nCheck eh logo apos, ou seja j+1
    }
    
}

int main() {

    int arr[] = {89, 34, 68, 90, 29, 34, 17};
    int n = sizeof(arr)/sizeof(int);
    //cout << "n = " << n << endl;

    InsertionSort(arr, n);

    for(int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // expected output: 17 29 34 34 68 89 90
    return 0;
}