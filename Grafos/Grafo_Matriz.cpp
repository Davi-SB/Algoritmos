#include <iostream>
#include <queue>
using namespace std;

class Graph {
private:
    int** matrix;
    int* mark;
    int numEdges, numNodes;
    const int UNVISITED = 0, VISITED = 1;
    void (Graph:: *traverse)(int) = nullptr;

    void pVerify(int *p)  { 
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); } 
    }

    void pVerify(int **p) {
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); }
    }

    int first(int currNode) {
        for (int i = 0; i < numNodes; i++) {
            if(matrix[currNode][i] != UNVISITED) return i; // ausencia
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o  vertice W
        for (int i = (w+1); i < numNodes; i++) {
            if(matrix[currNode][i] != UNVISITED) return i; // ausencia
        }
        return numNodes;
    }

    void setMark(int currNode, int state) { 
        mark[currNode] = state;
    }
    
    bool getMark(int currNode) {
        if(mark[currNode] == UNVISITED) return false;
        return true;
    }

    void preVisit(int currNode) { cout << currNode << "  "; }

    void posVisit(int currNode) { return; }

    void DFS(int currNode) {
        preVisit(currNode);

        setMark(currNode, VISITED);
        int nextNode = first(currNode);

        while(nextNode < numNodes) {
            if(getMark(nextNode) == UNVISITED)
                DFS(nextNode); // recursao --> pilha implicita
            nextNode = next(currNode, nextNode);
        }

        // posVisit(currNode);
    }

    void BFS(int start) {
        queue<int> nodeQueue;
        nodeQueue.push(start);
        setMark(start, VISITED);

        while (!nodeQueue.empty()) {
            int currNode = nodeQueue.front(); nodeQueue.pop();
            preVisit(currNode);
            int nextNode = first(currNode);

            while (nextNode < numNodes) {
                if(getMark(nextNode) == UNVISITED) {
                    setMark(nextNode, VISITED);
                    nodeQueue.push(nextNode);
                }
                nextNode = next(currNode, nextNode);
            }
            // posVisit(currNode);
        }
    }

public:
    Graph(int size) {
        this->matrix = new int*[size]; pVerify(matrix);
        for (int i = 0; i < size; i++) {
            this->matrix[i] = new int[size]; pVerify(matrix[i]);
        }
        this->mark = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
    }
    ~Graph() {
        for (int i = 0; i < numNodes; i++) delete[] matrix[i];
        delete[] matrix;
        delete[] mark;
    }

    void setEdge(int i, int j, int weight) {
        if(weight == 0) { cerr << "peso nulo"; exit(1); }
        if(matrix[i][j] == UNVISITED) numEdges++; // ausencia
        matrix[i][j] = weight;
    }

    void delEdge(int i, int j) {
        if(matrix[i][j] != UNVISITED) numEdges--; // ausencia
        matrix[i][j] = UNVISITED; // ausencia
    }

    void graphTraverse(int v, char searchType) { // "DFS" or "BFS" expected // 
        if(searchType == 'D') traverse = &Graph::DFS;
        else if(searchType == 'B') traverse = &Graph::BFS;
        else { cerr << "error searchType - graphTraverse" << endl; exit(1); }

        for(int i = 0; i < numNodes; i++) setMark(i, UNVISITED);

        for(int i = 0; i < numNodes; i++) {
            if(getMark(v) == UNVISITED) 
                (this->*traverse)(v);
        }
    }
};

int main () {

    int n, q; cin >> n >> q;
    Graph g(n);

    while(q--) {
        string op; cin >> op;
        int i, j;
        if(op == "add") {
            cin >> i >> j;
            g.setEdge(i, j, 1);
            g.setEdge(j, i, 1);
        }
        else  {
            cin >> i;
            if(op == "BSF") g.graphTraverse(i, 'B');
            else g.graphTraverse(i, 'D');
            cout << endl;
        }
    }

    return 0;
} // g++ Grafo_Matriz.cpp -o G && ./G < inputM.in