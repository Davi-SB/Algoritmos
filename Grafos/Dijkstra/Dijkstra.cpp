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

// Comparação baseada no custo
    bool operator > (const Trio& t) const { return this->cost > t.cost; }
    bool operator >= (const Trio& t) const { return this->cost >= t.cost; }
    bool operator < (const Trio& t) const { return this->cost < t.cost; }
    bool operator <= (const Trio& t) const { return this->cost <= t.cost; }
    //bool operator <=(Trio t) { return !((*this) > t); }
};

class Graph {
private:
    vector<Node>* graphList;
    bool* mark;
    int *distance, *parent;
    int numEdges, numNodes;
    const bool VISITED = true;

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    int first(int currNode) {
        if(!graphList[currNode].empty()) return graphList[currNode][0].index;
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o vertice W
        for(int i = 0; i < (int)graphList[currNode].size(); i++) {
            if(graphList[currNode][i].index == w) {
                if((i+1) < (int)graphList[currNode].size()) return graphList[currNode][i+1].index;
            }
        }
        return numNodes;
    }

    void setMark(int currNode, int state) { 
        mark[currNode] = state;
    }
    
    bool getMark(int currNode) {
        if(mark[currNode] == VISITED) return true;
        return false;
    }

public:
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark      = new bool[size];
        this->distance  = new int[size];
        this->parent    = new int[size];
        this->numNodes  = size;
        this->numEdges  = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
        delete[] this->distance;
        delete[] this->parent;
    }

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

    int weight(int i, int j) { // MELHORAR COM SET!!!!!     
        for(Node element : graphList[i]) {
            if(element.index == j) return element.weight;
        }
        cerr << "weight error" << endl; exit(1); 
    }

    void dijkstra(int start) {
        for (int i = 0; i < numNodes; i++) { // inicializacao
            distance[i] = INT_MAX;
            parent[i] = -1;
            setMark(i, !VISITED);
        }
        priority_queue< Trio, vector<Trio>, greater<Trio> > pq;
        
        pq.push(Trio(start, start, 0));
        distance[start] = 0;

        for (int i = 0; i < numNodes; i++) { // cada iteracao encontra o enesimo vertice mais proximo da origem. Evita casos em que o problema esta resolvido mas a heap ainda nao esta vazia
            Trio t;
            do {
                if(pq.empty()) return; // se a heap esta vazia, o algoritmo ja pode terminar
                t = pq.top(); pq.pop();
            } while(getMark(t.curr) == VISITED);
            setMark(t.curr, VISITED);
            parent[t.curr] = t.prev;

            int w = first(t.curr);
            while(w < numNodes) {
                int newPathWeight = weight(t.curr, w); // variavel evita duas buscas
                if(distance[w] > (distance[t.curr] + newPathWeight) && (getMark(w) == !VISITED)) {
                    distance[w] = distance[t.curr] + newPathWeight;
                    pq.push(Trio(t.curr, w, distance[w]));
                }
                w = next(t.curr, w);
            }
        }
    }

    void printDijkstra(int start) {
        dijkstra(start);
        for (int i = 0; i < numNodes; i++) {
            if(distance[i] == INT_MAX) cout << "-1 ";
            else cout << distance[i] << ' ';
        } cout << endl;
    }

};

int main () {
    int numNodes, numEdges, v; cin >> numNodes >> numEdges >> v;
    Graph grafo(numNodes);

    while(numEdges--) {
        int i, j, weight; cin >> i >> j >> weight;
        grafo.setEdge(i, j, weight);
        grafo.setEdge(j, i, weight);
    }

    grafo.printDijkstra(v); // expected 0 6 11 9 7 -1 -1 
    return 0;
} // g++ Dijkstra.cpp -o DJ && ./DJ < input.in

/*
7 6 0
0 1 6
2 3 2
4 0 7
2 1 15
3 1 3
5 6 12
*/