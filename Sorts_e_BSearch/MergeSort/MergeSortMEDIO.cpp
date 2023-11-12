#include <iostream>
using namespace std;

void Merge(int arr[], int left, int mid, int right) {
    int sizeL = mid - left + 1; // +1 inclui o elemento mid
    int sizeR = right - mid;

    int L[sizeL], R[sizeR];

    for (int i = 0; i < sizeL; i++) { // copia os elementos de arr para os aux L e R
        L[i] = arr[left + i];
    }
    for (int i = 0; i < sizeR; i++) {
        R[i] = arr[mid+1 + i];
    }
    
    int indexL = 0, indexR = 0, indexArr = left;
    
    while ((indexL < sizeL) && (indexR < sizeR)) {
        if(L[indexL] <= R[indexR]) {
            arr[indexArr] = L[indexL];
            indexL++;
        }
        else {
            arr[indexArr] = R[indexR];
            indexR++;
        }
        indexArr++;
    }
    
    while(indexL < sizeL) {
        arr[indexArr] = L[indexL];
        indexL++;
        indexArr++;
    }
    while(indexR < sizeR) {
        arr[indexArr] = R[indexR];
        indexR++;
        indexArr++;
    }
}

void MergeSort(int arr[], int left, int right) {
    if(left < right) {
        int mid = left + (int)((right - left) / 2); // ((right - left) / 2) == metade da variacao

        MergeSort(arr, left, mid); // mid-1 daria problema quando m == 0
        MergeSort(arr, mid+1, right);

        Merge(arr, left, mid, right);
    }
}

int main() {
    int arr[] = {89, 34, 68, 90, 29, 34, 17}; // expected output: 17 29 34 34 68 89 90
    int size = sizeof(arr)/sizeof(int);

    MergeSort(arr, 0, size-1);

    for(int x : arr) {
        cout << x << " ";
    } cout << endl;

    return 0;
}