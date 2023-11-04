#include <iostream>
using namespace std;

// Discounts - RESOLVIDA
// https://codeforces.com/problemset/problem/1132/B

void SwapInt(long long int arr[], long long int i, long long int j) {
    long long int aux = arr[i]; arr[i] = arr[j]; arr[j] = aux;
}

long long int Partition(long long int arr[], long long int left, long long int right) {
    long long int pivot = arr[left];
    long long int i = left, j = right+1;
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

void QuickSort(long long int arr[], long long int left, long long int right) {
    if(left < right) {
        long long int s = Partition(arr, left, right);
        QuickSort(arr, left, s-1);
        QuickSort(arr, s+1, right);
    }
}

int main() {
    long long int n; // number of chocolate bars in the shop
    long long int m; // (1 <= m <= n−1) the number of coupons you have
    long long int sum=0;
    cin >> n;
    long long int barsPrice[n];
    for (long long int i = 0; i < n; i++) { 
        cin >> barsPrice[i];
        sum += barsPrice[i];
    }
    QuickSort(barsPrice, 0, n-1);   
    cin >> m;
    for (long long int i = 0; i < m; i++) { 
        long long int cupon;
        cin >> cupon;
        cout << (sum - barsPrice[(n-cupon)]) << endl;
    }
    return 0;
}