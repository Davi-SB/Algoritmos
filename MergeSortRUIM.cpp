#include <iostream>
using namespace std;

// i_i --> index inicial
// i_f --> index final
// copy origemArr[i_i_origem..i_f_origem] to destinoArr[i_i_destino..(i_i_destino+(i_f_origem-i_i_origem))]
void InsertArray(int origemArr[], int i_i_origem, int i_f_origem, int destinoArr[], int i_i_destino) {
    while (i_i_origem <= i_f_origem) {
        destinoArr[i_i_destino] = origemArr[i_i_origem];
        i_i_origem++; 
        i_i_destino++;
    }
}

void CustomMalloc(int*& pointer, int size) {
    pointer = new int[size];
    if (pointer == nullptr) {
        cout << "Erro na alocacao de memoria" << endl;
        exit(1);
    }
}

//Merges two sorted arrays into one sorted array
//Input: Arrays B[0..p − 1] and C[0..q − 1] both sorted
//Output: Sorted array A[0..p + q − 1] of the elements of B and C
void Merge(int B[], int sizeB, int C[], int sizeC, int A[]) { // B e C sao arrays previamente ordenados, a recursividade garante isso. A eh o array que recebera o merge de B e C. sizeB + sizeC == sizeA
    int i=0, j=0, k=0; // i --> index que progride em B // j --> em C // k --> em A
    while((i < sizeB) && (j < sizeC)) { // roda enquanto nao chegar no ultimo elemento de um dos arrays
        if(B[i] <= C[j]) {
            A[k] = B[i];
            i++;
        }
        else {
            A[k] = C[j];
            j++;
        }
        k++;
    }

    while (i < sizeB) {
        A[k] = B[i];
        i++;
        k++;
    }
    while (j < sizeC) {
        A[k] = C[j];
        j++;
        k++;
    }
}

void MergeSort(int A[], int n) {
    if (n > 1) { // controla a recursao
        int *B = nullptr, *C = nullptr;
        int sizeB, sizeC;

        CustomMalloc(B, (n/2));
        CustomMalloc(C, n-(n/2));
        sizeB = n/2;
        sizeC = n-(n/2);

        InsertArray(A, 0, (sizeB-1), B, 0);
        InsertArray(A, sizeB, (n-1), C, 0);

        MergeSort(B, sizeB);
        MergeSort(C, sizeC);
        Merge(B, sizeB, C, sizeC, A);

        delete[] B;
        delete[] C;
    }
}

int main() {

    int arr[] = {89, 34, 68, 90, 29, 34, 17};
    int n = sizeof(arr)/sizeof(int);

    MergeSort(arr, n);

    for(int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // expected output: 17 29 34 34 68 89 90
    return 0;
}