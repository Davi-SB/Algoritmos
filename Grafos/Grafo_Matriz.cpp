#include <iostream>
#include <queue>
using namespace std;

class Graph {
private:
    int** matrix;
    int* mark;
    int numEdges, numNodes;
    const int UNVISITED = 0, VISITED = 1;
    void (Graph:: *traverse)(int v) = nullptr;

    void pVerify(int *p)  { 
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); } 
    }

    void pVerify(int **p) {
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); }
    }

    int first(int currNode) {
        for (int i = 0; i < (numNodes-1); i++) {
            if(matrix[currNode][i] != UNVISITED) return i; // ausencia
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o  vertice W
        for (int i = (w+1); i < (numNodes-1); i++) {
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

    void preVisit(int currNode) { return; }

    void posVisit(int currNode) { return; }

    void DFS(int currNode) {
        // preVisit(currNode);

        setMark(currNode, VISITED);
        int nextNode = first(currNode);

        while(nextNode < numNodes) {
            if(getMark(nextNode) == UNVISITED)
                DFS(nextNode);
            nextNode = next(currNode, nextNode);
        }

        // posVisit(currNode);
    }

    void BFS(int start) {
        queue<int> nodeQueue;
        nodeQueue.push(start);
        setMark(start, VISITED);

        while (nodeQueue.size() > 0) {
            int currNode = nodeQueue.front(); nodeQueue.pop();
            // preVisit(currNode);
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
        matrix = new int*[size]; pVerify(matrix);
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size]; pVerify(matrix[i]);
        }
        mark = new int[size];
        numNodes = size;
        numEdges = 0;
    }
    ~Graph() {
        for (int i = 0; i < (numNodes-1); i++) delete[] matrix[i];
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

    void graphTraverse(int v, char searchType[3]) { // "DFS" or "BFS" expected
        if(searchType[0] == 'D') traverse = DFS;
        if(searchType[0] == 'B') traverse = BFS;
        else { cerr << "error searchType - graphTraverse" << endl; exit(1); }

        for(int i = 0; i < (numEdges-1); i++) setMark(i, UNVISITED);

        for(int i = 0; i < (numEdges-1); i++) {
            if(getMark(v) == UNVISITED) 
                (this->*traverse)(v);
        }
    }
};

int main () {

    //

    return 0;
}