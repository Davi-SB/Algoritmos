#include <iostream>
using namespace std;

void Merge(int arr[], int left, int right, int size) {
    int temp[size];
    int mid = (left+right)/2;
    int i1 = left, i2 = mid+1; // mid+1!!! nao eh right

    for (int i = left; i <= right; i++){ // for de inicio e fim nao convencionais
        temp[i] = arr[i];
    }    

    for (int curr = left; curr <= right; curr++) { // for de inicio e fim nao convencionais
        if(i1==mid+1) arr[curr] = temp[i2++];
        else if(i2==right+1) arr[curr] = temp[i1++];
        else if(temp[i1] <= temp[i2]) arr[curr] = temp[i1++];
        else arr[curr] = temp[i2++];
    }
}

void MergeSort(int arr[], int left, int right, int size) {
    if(left < right) { // caso base da recursao mto importante
        int mid = (left+right)/2;
        MergeSort(arr, left, mid, size);
        MergeSort(arr, mid+1, right, size);
        Merge(arr, left, right, size); // MERGE SO, nao sort
    }
}

int Partition(int arr[], int left, int right) {
    int pivot = arr[left];
    int i = left, j = right+1; // aqui sim eh right, right+1 inclusive

    do { // lembrar de negar
        do {
            i++;
        } while((arr[i] < pivot) && (i < right)); 
        do {
            j--; // descresce!! --
        } while(arr[j] > pivot);
        swap(arr[i], arr[j]);
    } while(i < j);

    swap(arr[i], arr[j]);
    swap(arr[left], arr[j]);
    return j;
}

void QuickSort(int arr[], int left, int right) {
    if(left < right) {
        int s = Partition(arr, left, right);
        QuickSort(arr, left, s-1);
        QuickSort(arr, s+1, right);
    }
}

int BinarySearch(int arr[], int size, int key) {
    int left = 0, right = size-1;

    while (left <= right) {
        int mid = (left+right)/2;
        if(key == arr[mid]) return mid;
        else if(key < arr[mid]) right = mid-1;
        else left = mid+1;
    }
    return -1;
}

int main() {
    int arr[] = {89, 34, 68, 90, 29, 34, 17}; // expected output: 17 29 34 34 68 89 90
    int arr2[] = {89, 34, 68, 90, 29, 34, 17}; // expected output: 17 29 34 34 68 89 90
    int size = sizeof(arr)/sizeof(int);
    int key = 68;

    MergeSort(arr, 0, size-1, size); // 11min, 4 argumentos, size nao aparece no pseudo codigo
    QuickSort(arr2, 0, size-1); // 9min, tudo igual o pseudo codigo
    int BCreturn = BinarySearch(arr, size, key); // 4min, size nao aparece no pseudo codigo. versao recursiva tem left and right como argumentos, caso a busca seja em um subarray, pode ser interessante

    cout << "expected output: 17 29 34 34 68 89 90" << endl;
    cout << "MergeSort:       ";
    for(int x : arr) {
        cout << x << " ";
    } cout << endl;
    cout << "QuickSort:       ";
    for(int x : arr2) {
        cout << x << " ";
    } cout << endl;
    cout << "Binary Search: " << BCreturn << " (expected 4)" << endl;
    return 0;
}