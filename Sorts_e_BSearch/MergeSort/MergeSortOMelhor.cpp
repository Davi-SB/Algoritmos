#include <iostream>
using namespace std;

void Merge(int arr[], int l, int r, int size) {
    // obs: se atentar com a inicializacao e condicao de parada dos for dessa funcao    
    int m = (int)((l + r) / 2); // metade do subarrray
    int i1 = l, i2 = m+1; // index inicial de cada um dos dois subarrays. sub1[l..m], sub2[m+1..r]
    int temp[size];

    for (int i = l; i <= r; i++){ temp[i] = arr[i]; } // copia os elementos em questão de arr para temp na mesma posicao
    
    for (int curr = l; curr <= r; curr++) {
        if(i1 > m)      arr[curr] = temp[i2++]; // atribui o resto. (i1 > m) significa que i1 invadiu sub2
        else if(i2 > r) arr[curr] = temp[i1++]; // atribui o resto. (i2 > r) significa que i2 ja esgotou sub2

        else if(temp[i1] <= temp[i2]) arr[curr] = temp[i1++];
        else                          arr[curr] = temp[i2++];
    }
}

void MergeSort(int arr[], int l, int r, int size) {
    if(l < r) {
        int m = (int)((l + r) / 2); // metade do subarrray
        MergeSort(arr, l, m, size); // m-1 daria problema quando m == 0
        MergeSort(arr, m+1, r, size);

        Merge(arr, l, r, size);
    }
}

int main() {
    int arr[] = {89, 34, 68, 90, 29, 34, 17}; // expected output: 17 29 34 34 68 89 90
    int size = sizeof(arr)/sizeof(int);

    MergeSort(arr, 0, size-1, size);

    for(int x : arr) {
        cout << x << " ";
    } cout << endl;

    return 0;
}