#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {
private:
    int** mat;
    int numEdges, numNodes;

    void pVerify(int *p)  { 
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); } 
    }

    void pVerify(int **p) {
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); }
    }

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    void checkWeight(int weight) {
        if(weight) return;
        cerr << "null weight" << endl; exit(1);
    }


public:
    Graph(int size) {
        this->numEdges = 0;
        this->numNodes = size;
        this->mat = new int*[size]; pVerify(mat);
        for (int i = 0; i < size; i++) {
            this->mat[i] = new int[size]; pVerify(mat[i]);
            for (int j = 0; j < size; j++) mat[i][j] = INT_MAX; // prepara a matriz para o algoritmo
        }
    }
    ~Graph() {
        for (int i = 0; i < numNodes; i++) delete[] mat[i];
        delete[] mat;
    }

    void setEdge(int i, int j, int weight) {
        checkNode(i); checkNode(j); checkWeight(weight);
        if(mat[i][j] == INT_MAX) numEdges++; // ausencia
        mat[i][j] = weight;
    }

    void delEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(mat[i][j] != INT_MAX) numEdges--; // nao ausencia
        mat[i][j] = INT_MAX; // ausencia
    }

    void floyd() {
        for (int i = 0; i < numNodes; i++) mat[i][i] = 0; // segunda preparacao para o algoritmo
        
        for (int k = 0; k < numNodes; k++) { // V intermediario
            for (int i = 0; i < numNodes; i++) { // V1
                for (int j = 0; j < numNodes; j++) { // V2
                    if((mat[i][k] != INT_MAX) && (mat[i][j] > (mat[i][k] + mat[k][j]))) {
                        mat[i][j] = (mat[i][k] + mat[k][j]);
                    }
                }
            }
        }
    }

};

int main () {


    return 0;
} // g++ Grafo_Matriz.cpp -o G && ./G < inputM.in