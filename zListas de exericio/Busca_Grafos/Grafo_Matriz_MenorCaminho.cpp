#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {
private:
    int** matrix;
    int* mark;
    int* distance;
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

    int first(int currNode) {
        for (int i = 0; i < numNodes; i++) {
            if(matrix[currNode][i] == 1) return i; // ausencia
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o  vertice W
        for (int i = (w+1); i < numNodes; i++) {
            if(matrix[currNode][i] == 1) return i; // ausencia
        }
        return numNodes;
    }

    void setMark(int currNode, int state) { 
        mark[currNode] = state;
    }
    
    int getMark(int currNode) {
        if(mark[currNode] == 0) return 0;
        return 1;
    }

    //void preVisit(int currNode) { cout << currNode << "  "; }

    //void posVisit(int currNode) { return; }

    void BFSDistance(int start) {
        queue<int> nodeQueue;
        nodeQueue.push(start);
        setMark(start, 1);
        distance[start] = 0;

        while (!nodeQueue.empty()) {
            int currNode = nodeQueue.front(); 
            nodeQueue.pop();
            int nextNode = first(currNode);
            cout << "curr node: " << currNode << " // " << "first node: " << nextNode << endl;

            while (nextNode < numNodes) {
                if(getMark(nextNode) == 0) {
                    setMark(nextNode, 1);
                    // na primeira vez que eh visitado, eh possivel definir a menor das distancias
                    distance[nextNode] = distance[currNode] + 1; // dsitancia do atual + 1 (ele)
                    //
                    cout << " - set node " << nextNode << " to " << distance[nextNode] << endl;
                    //
                    nodeQueue.push(nextNode);
                }
                nextNode = next(currNode, nextNode);
            }
        }
    }

public:
    Graph(int size) {
        this->matrix = new int*[size]; pVerify(matrix);
        for (int i = 0; i < size; i++) {
            this->matrix[i] = new int[size]; pVerify(matrix[i]);
        }
        this->mark = new int[size];
        this->distance = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
    }
    ~Graph() {
        for (int i = 0; i < numNodes; i++) delete[] matrix[i];
        delete[] matrix;
        delete[] mark;
        delete[] distance;
    }

    void setEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(matrix[i][j] == 0) numEdges++; // ausencia
        matrix[i][j] = 1;

        if(matrix[j][i] == 0) numEdges++; // ausencia
        matrix[j][i] = 1;
    }

    void delEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(matrix[i][j] != 0) numEdges--; // ausencia
        matrix[i][j] = 0; // ausencia
    }

    int* MinDistances(int start) {
        checkNode(start);
        for(int i = 0; i < numNodes; i++){
            setMark(i, 0); // UNVISITED para esse caso
            distance[i] = INT_MAX;
        } 

        BFSDistance(start);
        // desse ponto, distance[i] == -1 significa que nao ha como sair de start e chegar em i
        return distance;
    }
};

int main () {
    /*
    int nodes, edges, i, j; 
    cin >> nodes >> edges;
    Graph g(nodes);

    for (int k = 0; k < edges; k++) {
        cin >> i >> j;
        g.setEdge(i, j);
    }
    */
    int nodes = 13;
    Graph g(nodes);
    g.setEdge(1, 2);
    g.setEdge(1, 4);
    //g.setEdge(2, 1);
    g.setEdge(2, 3);
    g.setEdge(2, 4);
    g.setEdge(2, 7);
    g.setEdge(2, 11);
    //g.setEdge(3, 2);
    //g.setEdge(4, 1);
    //g.setEdge(4, 2);
    g.setEdge(4, 5);
    //g.setEdge(5, 4);
    g.setEdge(6, 8);
    //g.setEdge(7, 2);
    g.setEdge(7, 9);
    //g.setEdge(8, 6);
    //g.setEdge(9, 7);
    g.setEdge(9, 10);
    //g.setEdge(10, 9);
    g.setEdge(10, 12);
    //g.setEdge(11, 2);
    g.setEdge(11, 12);
    //g.setEdge(12, 10);
    //g.setEdge(12, 11);

    int* distance = g.MinDistances(2);

    for (int k = 0; k < nodes; k++) {
        cout << k << " --> " << distance[k] << endl;
    }
    cout << endl << distance[10] << endl;
    return 0;
} // g++ Grafo_Matriz_MenorCaminho.cpp -o G && ./G < inputM.in

/*
13 24
1 2
1 4
2 1
2 3
2 4
2 7
2 11
3 2
4 1
4 2
4 5
5 4
6 8
7 2
7 9
8 6
9 7
9 10
10 9
10 12
11 2
11 12
12 10
12 11

----

0 --> -1
1 --> 1
2 --> 0
3 --> 1
4 --> 1
5 --> 2
6 --> -1
7 --> 1
8 --> -1
9 --> 2
10 --> 3
11 --> 1
12 --> 2
*/