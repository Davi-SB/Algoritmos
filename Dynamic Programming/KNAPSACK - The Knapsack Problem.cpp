#include <iostream>
using namespace std;

// https://www.spoj.com/problems/KNAPSACK/

class KnapSack {
private:
    int numItens, capacitySack;
    int *w, *v, **mat;

public:
    KnapSack(int n, int c) {
        this->numItens = n;
        this->capacitySack = c;
        w = new int[n+1];
        v = new int[c+1];

        // [n+1] x [capacity+1] mat
        mat = new int*[n+1];
        for (int i = 0; i < n; i++) mat[i] = new int[c+1];
        
    }
    ~KnapSack() {
        delete[] w;
        delete[] v;
        for (int i = 0; i < numItens; i++) delete[] mat[i];
        delete[] mat;
    }

    int run() {
        for (int i = 0; i < numItens+1; i++) {
            for (int j = 0; j < capacitySack+1; j++) {
                if(!i || !j) continue; // mat[i][j] = 0;
                if(w[i] <= j) mat[i][j] = max(mat[i-1][j], v[i] + mat[i-1][j-w[i]]);
                else mat[i][j] = mat[i-1][j];
            }
        }
        return mat[numItens][capacitySack];
    }
}; 

int main() {


    return 0;
}