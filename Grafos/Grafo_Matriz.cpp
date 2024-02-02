#include <iostream>
using namespace std;

class Graph {
private:
    int** matrix;
    int* mark;
    int numEdges, numNodes;

    void pVerify(int *p)  { if(p == nullptr) { cerr << "memory error" << endl; exit(1); } }

    void pVerify(int **p) { if(p == nullptr) { cerr << "memory error" << endl; exit(1); } }

    int first(int v) {
        for (int i = 0; i < (numEdges-1); i++) {
            if(matrix[v][i] != 0) return i; // ausencia
        }
        return numEdges;
    }

    int next(int v, int w) { // primeiro em que V se liga apos o  vertice W
        for (int i = (w+1); i < (numEdges-1); i++) {
            if(matrix[v][i] != 0) return i; // ausencia
        }
        return numEdges;
    }

public:
    Graph(int size) {
        matrix = new int*[size]; pVerify(matrix);
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size]; pVerify(matrix[i]);
        }
        mark = new int[size];
        numNodes = size;
        numEdges = 0;
    }
    ~Graph() {
        for (int i = 0; i < numNodes; i++) delete[] matrix[i];
        delete[] matrix;
    }

    void setEdge(int i, int j, int weight) {
        if(weight == 0) { cerr << "peso nulo"; exit(1); }
        if(matrix[i][j] == 0) numEdges++; // ausencia
        matrix[i][j] = weight;
    }

    void delEdge(int i, int j) {
        if(matrix[i][j] != 0) numEdges--; // ausencia
        matrix[i][j] = 0; // ausencia
    }
};

int main () {

    //

    return 0;
}