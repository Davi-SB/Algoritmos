#include <iostream>
using namespace std;

int Partition(int arr[], int l, int r) {
    int pivot = arr[l], i = l, j = r+1;

    do {
        do { i++; } while((arr[i] < pivot) && (i < r)); // enquanto os elementos mais da *esquerda* forem *menores* que o pivot        
        do { j--; } while(arr[j] > pivot); // enquanto os elementos mais da *direita* forem *maiores* que o pivot

        swap(arr[i], arr[j]);
    } while(i < j);

    swap(arr[i], arr[j]); // undo-swap arr[i] e arr[j] // desfazer ultimo swap. esse eh sempre um excesso. quando i>=j
    swap(arr[l], arr[j]); // manda o pivot pra posicao correta
    return j; // index do pivot ao fim da particao, a poosicao correta que ele ja esta
}

void QuickSort(int arr[], int l, int r) {
    if(l < r) {
        int s = Partition(arr, l, r);
        QuickSort(arr, l, s-1);
        QuickSort(arr, s+1, r);
    }
}

int main() {
    int arr[] = {89, 34, 68, 90, 29, 34, 17}; // expected output: 17 29 34 34 68 89 90
    int size = sizeof(arr)/sizeof(int);

    QuickSort(arr, 0, size-1);

    for(int x : arr) {
        cout << x << " ";
    } cout << endl;

    return 0;
}