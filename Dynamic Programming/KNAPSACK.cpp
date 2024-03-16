#include <iostream>
using namespace std;

class KnapSack {
private:
    int numItens, capacity;
    int *w, *v, **mat;
    int indexIt;

    void printLine() {
        for (int j = 0; j < capacity+1; j++) cout << "-----";
        cout << '-' << endl;
    }

    void printMat() {
        printLine();
        for (int i = 0; i < numItens+1; i++) {
            cout << "| ";
            for (int j = 0; j < capacity+1; j++) {
                if(mat[i][j] != -1) printf("%.2d | ", mat[i][j]); //cout << mat[i][j] << " | ";
                else cout << "-- | ";
            } cout << endl;
            printLine();
        }
        cout << endl << endl;
    }

    void topDownSetup() {
        for (int i = 1; i < numItens+1; i++) {
            for (int j = 1; j < capacity+1; j++) {
                mat[i][j] = -1;
            }
        }
    } 
public:
    KnapSack(int numItens, int capacity) {
        this->indexIt = 0; // 0-based array
        this->numItens = numItens;
        this->capacity = capacity;
        this->w = new int[numItens];
        this->v = new int[numItens];

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
    
    void pushItem(int weight, int value) {
        v[indexIt] = value; 
        w[indexIt] = weight;
        indexIt++;
    }

    int runBottomUp() {
        for (int i = 0; i < numItens+1; i++) {
            for (int j = 0; j < capacity+1; j++) {
                if(i == 0 || j == 0) mat[i][j] = 0;
                else if(w[i-1] <= j) mat[i][j] = max(mat[i-1][j], v[i-1] + mat[i-1][j-w[i-1]]);
                else mat[i][j] = mat[i-1][j];
            }
        }
        printMat();
        return mat[numItens][capacity];
    }

    int runTopDownHelp(int i, int j) {
        if(mat[i][j] < 0) {
            int value = 12345;
            if(j < w[i-1]) value = runTopDownHelp(i-1, j);
            else value = max(runTopDownHelp(i-1, j), v[i-1] + runTopDownHelp(i-1, j - w[i-1]));
            mat[i][j] = value;
        }
        return mat[i][j];
    }

    int runTopDown() {
        topDownSetup();
        runTopDownHelp(numItens, capacity);
        printMat();
        return mat[numItens][capacity];
    }
}; 

int main() {
    int capacity, numItens; cin >> capacity >> numItens;
    KnapSack sack(numItens, capacity); 

    for (int i = 0; i < numItens; i++) {
        int w, v; cin >> w >> v;
        sack.pushItem(w, v);
    }
    sack.runBottomUp();
    sack.runTopDown();
    return 0;
} // g++ KNAPSACK.cpp -o knap && ./knap < input.in > output.out

/*
6 4

2 15
3 50
2 20
3 25
*/ 
 
/*
10 4

2 10
5 60
4 30
3 50
*/