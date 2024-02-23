#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;

class Node {
private:
    friend class Graph;
    int index, weight;

public:
    Node(int index, int weight) {
        this->index = index;
        this->weight = weight;
    }
    ~Node() {}
};

class Trio {
private:
    friend class Graph;
    int prev, curr, cost;

public:
    Trio(int prev, int curr, int cost) {
        this->prev = prev;
        this->curr = curr;
        this->cost = cost;
    }
    Trio() {}
    ~Trio() {}
    bool operator > (const Trio& t) const { return this->cost > t.cost; }
};

class Graph {
private:
    vector<Node>* graphList;
    bool* mark;
    int *distance, *parent;
    int numEdges, numNodes, itNext;
    const bool VISITED = true;

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    Node first(int currNode) {
        if(!graphList[currNode].empty()) return graphList[currNode][0];
        return Node(numNodes, numNodes);
    }

    Node next(int currNode) {
        if(itNext+1 < graphList[currNode].size()) {
            itNext++;
            return graphList[currNode][itNext];
        }
        itNext = 0;
        return Node(numNodes, numNodes);
    }

public:
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark      = new bool[size];
        this->distance  = new int[size];
        this->parent    = new int[size];
        this->numNodes  = size;
        this->numEdges  = 0;
        this->itNext    = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
        delete[] this->distance;
        delete[] this->parent;
    }

    int NumNodes() { return numNodes; }

    void setEdge(int a, int b, int weight) {
        checkNode(a); checkNode(b);
        Node temp(b, weight);
        graphList[a].push_back(temp);
        numEdges++;
    }

    void delEdge(int a, int b) {
        checkNode(a); checkNode(b);
        if(graphList[a].empty()) return;

        int i=0;
        bool found = false;
        for(; (i < (int)graphList[a].size()) && (!found); i++) 
            if(graphList[a][i].index == b) found = true;

        if(found) {
            i--;
            graphList[a].erase(graphList[a].begin() + i); // O(n)
            numEdges--;
        }
    }

    void prim() {
        for (int i = 0; i < numNodes; i++) { // inicializacao
            distance[i] = INT_MAX;
            parent[i] = -1;
            mark[i] = !VISITED;
        }
        priority_queue< Trio, vector<Trio>, greater<Trio> > pq;
        pq.push(Trio(0, 0, 0));
        distance[0] = 0;

        for (int i = 0; i < numNodes; i++) { // cada iteracao encontra o enesimo vertice mais proximo da origem. Evita casos em que o problema esta resolvido mas a heap ainda nao esta vazia
            Trio t;
            do {
                if(pq.empty()) return; // se a heap esta vazia, o algoritmo ja pode terminar
                t = pq.top(); pq.pop();
            } while(mark[t.curr] == VISITED);
            mark[t.curr] = VISITED;
            parent[t.curr] = t.prev;

            Node n = first(t.curr);
            while(n.index < numNodes) {
                if(distance[n.index] > n.weight && (mark[n.index] == !VISITED)) {
                    distance[n.index] = n.weight;
                    pq.push(Trio(t.curr, n.index, distance[n.index]));
                }
                n = next(t.curr);
            }
        }
    }

    void MST() {
        prim();
        //int** temp;
        //temp[0] = parent;
        //temp[1] = distance;
        //return temp;
    }

    void printMST() {
        prim();
        for (int i = 0; i < numNodes; i++) {
            cout << parent[i] << "  ";
        } cout << endl;
        for (int i = 0; i < numNodes; i++) {
            cout << distance[i] << "  ";
        } cout << endl;
    }

};

int main () {
    int numNodes, numEdges; cin >> numNodes >> numEdges;
    Graph grafo(numNodes);

    while(numEdges--) {
        int i, j, weight; cin >> i >> j >> weight;
        grafo.setEdge(i, j, weight);
        grafo.setEdge(j, i, weight);
    }

    grafo.printMST(); // expected  
    return 0;
} // g++ Prim.cpp -o DJ && ./DJ < input.in > output.out

/*
5 7

1 2 10
1 3  3
1 4 20
2 3  2
2 4  5
3 5 15
4 5 11
*/