#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Graph {
private:
    vector<int>* graphList;
    int* mark;
    int* distance;
    int numEdges, numNodes, itNext;
    const int UNVISITED = 0, VISITED = 1;

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    int first(int currNode) {
        if(!graphList[currNode].empty()) return graphList[currNode][0];
        return numNodes;
    }

    int next(int currNode) {
        if(itNext+1 < graphList[currNode].size()) {
            itNext++;
            return graphList[currNode][itNext];
        }
        itNext = 0;
        return numNodes;
    }

    void setMark(int currNode, int state) { 
        mark[currNode] = state;
    }
    
    bool getMark(int currNode) {
        if(mark[currNode] == UNVISITED) return false;
        return true;
    }

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
                nextNode = next(currNode);
            }
        }
    }

public:
    Graph(int size) {
        this->graphList = new vector<int>[size];
        this->mark = new int[size];
        this->distance = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
        this->itNext = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
        delete[] this->distance;
    }

    void setEdge(int a, int b, int weight) {
        checkNode(a); checkNode(b);
        graphList[a].push_back(b);
        numEdges++;
    }

    void delEdge(int a, int b) {
        checkNode(a); checkNode(b);
        if(graphList[a].empty()) return;

        int i=0;
        bool found = false;
        for(; (i < (int)graphList[a].size()) && (!found); i++) 
            if(graphList[a][i] == b) found = true;

        if(found) {
            i--;
            graphList[a].erase(graphList[a].begin() + i); // O(n)
            numEdges--;
        }
    }

    int* MinDistances(int start) {
        checkNode(start);
        for(int i = 0; i < numNodes; i++) {
            setMark(i, 0); // UNVISITED para esse caso
            distance[i] = -1;
        } 
        BFSDistance(start);
        // desse ponto, distance[i] == -1 significa que nao ha como sair de start e chegar em i
        return distance;
    }
};

int main () { // essa implementação não considera multigrafos visto que isso nao faria sentido sem arestas ponderadas
    int nodes = 13;
    Graph g(nodes);
    g.setEdge(1, 2, 1);
    g.setEdge(1, 4, 1);
    g.setEdge(2, 1, 1);
    g.setEdge(2, 3, 1);
    g.setEdge(2, 4, 1);
    g.setEdge(2, 7, 1);
    g.setEdge(2, 11, 1);
    g.setEdge(3, 2, 1);
    g.setEdge(4, 1, 1);
    g.setEdge(4, 2, 1);
    g.setEdge(4, 5, 1);
    g.setEdge(5, 4, 1);
    g.setEdge(6, 8, 1);
    g.setEdge(7, 2, 1);
    g.setEdge(7, 9, 1);
    g.setEdge(8, 6, 1);
    g.setEdge(9, 7, 1);
    g.setEdge(9, 10, 1);
    g.setEdge(10, 9, 1);
    g.setEdge(10, 12, 1);
    g.setEdge(11, 2, 1);
    g.setEdge(11, 12, 1);
    g.setEdge(12, 10, 1);
    g.setEdge(12, 11, 1);

    int* distance = g.MinDistances(2);

    for (int k = 0; k < nodes; k++) {
        cout << k << " --> " << distance[k] << endl;
    }
    return 0;
} // g++ Grafo_ListaAdj_MenorCaminho.cpp -o G && ./G

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