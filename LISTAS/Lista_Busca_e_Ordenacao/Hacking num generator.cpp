#include <iostream>
using namespace std;

// Hacking the random number generator - RESOLVIDA
// https://www.spoj.com/problems/HACKRNDM/

void Merge(int arr[], int left, int right, int size) {   
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

int BinarySearch(int arr[], int size, int key) {
    int left = 0, right = size-1; 
    while (left <= right) { // enquando os indices nao se cruzam
        int mid = (int)(left + right) / 2;
        if(key == arr[mid]) return 1;
        else if(key < arr[mid]) right = mid-1;
        else left = mid+1;
    }
    return 0; // key nao encotrada
}

int main() {
    int n, k, cont=0; 
    int i;
    cin >> n;
    cin >> k;
    int arr[n]; // declarar o array apos ja ter o valor de n
    for (i = 0; i < n; i++) { cin >> arr[i]; } // armazena a entrada
    MergeSort(arr, 0, n-1, n); // ordena o vetor de entrada
    for (int i = 0; i < n; i++) {
        if(BinarySearch(arr, n, arr[i]+k)) cont++;
    } // a[i] - a[j] == k
    cout << cont;
    return 0;
}