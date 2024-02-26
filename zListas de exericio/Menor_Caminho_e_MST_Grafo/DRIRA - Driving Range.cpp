#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;

//  SOLVED - https://www.spoj.com/problems/DRIRA/

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
    int numEdges, numNodes, itNext;
    const bool VISITED = true;

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
    vector<int> distance, parent; // modificacao para deixar a questao mais acessivel na main
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark      = new bool[size];
        this->numNodes  = size;
        this->numEdges  = 0;
        this->itNext    = 0;
        this->distance.resize(size);
        this->parent.resize(size);
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
    }

    int NumNodes() { return numNodes; }

    void setEdge(int a, int b, int weight) {
        Node temp(b, weight);
        graphList[a].push_back(temp);
        numEdges++;
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

    void MST() { prim(); }
};

int main () {
    int numNodes, numEdges;
    while((cin >> numNodes >> numEdges) && (numNodes || numEdges)) {
        Graph grafo(numNodes);
        while(numEdges--) {
            int i, j, weight; cin >> i >> j >> weight;
            grafo.setEdge(i, j, weight);
            grafo.setEdge(j, i, weight);
        }

        grafo.MST();
        sort(grafo.distance.begin(), grafo.distance.end());
        
        int ultimo = grafo.distance[grafo.distance.size()-1]; // variavel para faciliar a leitura
        if(ultimo == INT_MAX) cout << "IMPOSSIBLE" << endl;
        else cout << ultimo << endl;
    }
    return 0;
}