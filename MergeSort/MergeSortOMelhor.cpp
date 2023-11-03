#include <iostream>
using namespace std;

void Merge(int arr[], int left, int right, int size) {
    // obs: se atentar com a inicializacao e condicao de parada dos for dessa funcao    
    int mid = (int)((left + right) / 2); // metade do subarrray
    int index1 = left, index2 = mid+1; // index inicial de cada um dos dois subarrays. sub1[left..mid], sub2[mid+1..right]
    int temp[size];

    for (int i = left; i <= right; i++){ temp[i] = arr[i]; } // copia os elementos em questão de arr para temp na mesma posicao
    
    for (int curr = left; curr <= right; curr++) {
        if(index1 > mid) arr[curr] = temp[index2++]; // atribui o resto. (index1 > mid) significa que index1 invadiu sub2
        else if(index2 > right) arr[curr] = temp[index1++]; // atribui o resto. (index2 > right) significa que index2 ja esgotou sub2

        else if(temp[index1] <= temp[index2]) arr[curr] = temp[index1++];
        else arr[curr] = temp[index2++];
    }   
}

void MergeSort(int arr[], int left, int right, int size) {
    if(left < right) {
        int mid = (int)((left + right) / 2); // metade do subarrray

        MergeSort(arr, left, mid, size); // mid-1 daria problema quando m == 0
        MergeSort(arr, mid+1, right, size);

        Merge(arr, left, right, size);
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