#include <iostream>
using namespace std;

int BinarySearch(int arr[], int size, int key) {
    int left = 0, right = size-1;
    
    while (left <= right) { // enquando os indices nao se cruzam
        int mid = (int)(left + right) / 2;

        if(key == arr[mid]) return key;

        else if(key < arr[mid]) right = mid-1;
        else left = mid+1;
    }
    return -1; // key nao encotrada
}

int main() {

    int arr[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int size = sizeof(arr)/sizeof(arr[0]);

    int key, awnser; 
    cout << "Insira o numero buscado: "; cin >> key;

    awnser = BinarySearch(arr, size, key);

    (awnser!=-1) ? cout << "O numero " << key << " foi encontrado no array" : cout << "Numero " << key << " nao encontrado"; cout << endl; 

    return 0;
}