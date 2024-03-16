#include <iostream>
using namespace std;

// SOLVED - https://www.spoj.com/problems/KNAPSACK/

class KnapSack {
private:
    int numItems, capacity;
    int *w, *v, **mat;
    int indexIt;
public:
    KnapSack(int numItems, int capacity) {
        this->indexIt = 0; // 0-based array
        this->numItems = numItems;
        this->capacity = capacity;
        this->w = new int[numItems];
        this->v = new int[numItems];

        // [n+1] x [capacity+1] mat
        this->mat = new int*[numItems+1];
        for (int i = 0; i < numItems+1; i++) this->mat[i] = new int[capacity+1];
    }
    ~KnapSack() {
        delete[] w;
        delete[] v;
        for (int i = 0; i < numItems+1; i++) delete[] mat[i];
        delete[] mat;
    }
    
    void pushItem(int value, int weight) {
        v[indexIt] = value; 
        w[indexIt] = weight;
        indexIt++;
    }

    int run() {
        for (int i = 0; i < numItems+1; i++) {
            for (int j = 0; j < capacity+1; j++) {
                if(i == 0 || j == 0) mat[i][j] = 0;
                else if(w[i-1] <= j) mat[i][j] = max(mat[i-1][j], v[i-1] + mat[i-1][j-w[i-1]]);
                else mat[i][j] = mat[i-1][j];
            }
        }
        return mat[numItems][capacity];
    }
}; 

int main() {
    int capacity, numItems; cin >> capacity >> numItems;
    KnapSack sack(numItems, capacity); 

    for (int i = 0; i < numItems; i++) {
        int w, v; cin >> w >> v;
        sack.pushItem(v, w);
    }
    cout << sack.run();
    return 0;
}

// seg fault
/*#include <iostream>
using namespace std;

// https://www.spoj.com/problems/KNAPSACK/

class KnapSack {
private:
    int numItens, capacity;
    int *w, *v, **mat;
    int indexIt;
public:
    KnapSack(int numItens, int capacity) {
        this->indexIt = 1; // 1-based array
        this->numItens = numItens;
        this->capacity = capacity;
        this->w = new int[numItens+1];
        this->v = new int[numItens+1];

        // [n+1] x [capacity+1] mat
        this->mat = new int*[numItens+1];
        for (int i = 0; i < numItens+1; i++) this->mat[i] = new int[capacity+1];
    }
    ~KnapSack() {
        delete[] w;
        delete[] v;
        for (int i = 0; i < numItens+1; i++) delete[] mat[i];
        delete[] mat;
    }
    
    void pushItem(int value, int weight) {
        v[indexIt] = value; 
        w[indexIt] = weight;
        indexIt++;
    }

    int run() {
        for (int i = 0; i < numItens+1; i++) {
            for (int j = 0; j < capacity+1; j++) {
                if(!i || !j) mat[i][j] = 0;
                if(w[i] <= j) mat[i][j] = max(mat[i-1][j], v[i] + mat[i-1][j-w[i]]);
                else mat[i][j] = mat[i-1][j];
            }
        }
        return mat[numItens][capacity];
    }
}; 

int main() {
    int capacity, numItens; cin >> capacity >> numItens;
    KnapSack sack(numItens, capacity); 

    for (int i = 0; i < numItens; i++) {
        int w, v; cin >> w >> v;
        sack.pushItem(v, w);
    }

    cout << sack.run();
    return 0;
}*/