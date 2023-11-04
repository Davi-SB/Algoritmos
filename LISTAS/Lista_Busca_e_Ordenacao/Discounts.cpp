#include <iostream>
using namespace std;

// Discounts - nao resolvida
// https://codeforces.com/problemset/problem/1132/B

void Merge(long long int arr[], long long int left, long long int right, long long int size) {
    // obs: se atentar com a inicializacao e condicao de parada dos for dessa funcao    
    long long int mid = ((left + right) / 2); // metade do subarrray
    long long int index1 = left, index2 = mid+1; // index inicial de cada um dos dois subarrays. sub1[left..mid], sub2[mid+1..right]
    long long int temp[size];

    for (long long int i = left; i <= right; i++){ temp[i] = arr[i]; } // copia os elementos em questão de arr para temp na mesma posicao
    
    for (long long int curr = left; curr <= right; curr++) {
        if(index1 > mid) arr[curr] = temp[index2++]; // atribui o resto. (index1 > mid) significa que index1 invadiu sub2
        else if(index2 > right) arr[curr] = temp[index1++]; // atribui o resto. (index2 > right) significa que index2 ja esgotou sub2

        else if(temp[index1] <= temp[index2]) arr[curr] = temp[index1++];
        else arr[curr] = temp[index2++];
    }   
}

void MergeSort(long long int arr[], long long int left, long long int right, long long int size) {
    if(left < right) {
        long long int mid = ((left + right) / 2); // metade do subarrray

        MergeSort(arr, left, mid, size); // mid-1 daria problema quando m == 0
        MergeSort(arr, mid+1, right, size);

        Merge(arr, left, right, size);
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

    MergeSort(barsPrice, 0, n-1, n);
    
    cin >> m;
    long long int cupons[m];

    for (long long int i = 0; i < m; i++) { 
        cin >> cupons[i];
        cout << (sum - barsPrice[(n-cupons[i])]) << endl;
    }


    return 0;
}