#include <iostream>
using namespace std;

void SwapInt(int arr[], int i, int j) {
    int aux = arr[i]; arr[i] = arr[j]; arr[j] = aux;
}

int Partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left, j = right+1;

    do {
        do {
            i++;
        } while((arr[i] < pivot) && (i < right)); // enquanto os elementos mais da *esquerda* forem *menores* que o pivot        
        
        do {
            j--;
        } while(arr[j] > pivot); // enquanto os elementos mais da *direita* forem *maiores* que o pivot

        SwapInt(arr, i, j); // swap arr[i] e arr[j]
    } while(i < j);

    SwapInt(arr, i, j); // undo-swap arr[i] e arr[j] // desfazer ultimo swap. esse eh sempre um excesso. quando i>=j
    SwapInt(arr, left, j); // swap arr[left] e arr[j]. manda o pivot pra posicao correta
    return j; // index do pivot ao fim da particao, a poosicao correta que ele ja esta
}

void QuickSort(int arr[], int left, int right) {
    if(left < right) {
        int s = Partition(arr, left, right);

        QuickSort(arr, left, s-1);
        QuickSort(arr, s+1, right);
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