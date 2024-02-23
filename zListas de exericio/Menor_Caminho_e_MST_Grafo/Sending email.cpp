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
    bool operator < (const Node& n) const { return this->index < n.index; }
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

    void dijkstra(int start, int destination) {
        for (int i = 0; i < numNodes; i++) { // inicializacao
            distance[i] = INT_MAX;
            parent[i] = -1;
            mark[i] = !VISITED;
        }
        priority_queue< Trio, vector<Trio>, greater<Trio> > pq;
        
        pq.push(Trio(start, start, 0));
        distance[start] = 0;

        for (int i = 0; i < numNodes; i++) { // cada iteracao encontra o enesimo vertice mais proximo da origem. Evita casos em que o problema esta resolvido mas a heap ainda nao esta vazia
            Trio t;
            do {
                if(pq.empty()) return; // se a heap esta vazia, o algoritmo ja pode terminar
                t = pq.top(); pq.pop();
            } while(mark[t.curr] == VISITED);
            mark[t.curr] = VISITED;
            if(mark[destination]) return;
            parent[t.curr] = t.prev;

            Node n = first(t.curr);
            while(n.index < numNodes) {
                if(distance[n.index] > (distance[t.curr] + n.weight) && (mark[n.index] == !VISITED)) {
                    distance[n.index] = distance[t.curr] + n.weight;
                    pq.push(Trio(t.curr, n.index, distance[n.index]));
                }
                n = next(t.curr);
            }
        }
    }

public:
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark      = new bool[size];
        this->distance  = new int[size];
        this->parent    = new int[size];
        this->numNodes  = size;
        this->numEdges  = 0;
        this->itNext = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
        delete[] this->distance;
        delete[] this->parent;
    }

    void setEdge(int a, int b, int weight) {
        graphList[a].push_back(Node(b, weight));
        numEdges++;
    }

    int getDistance(int start, int destination) {
        dijkstra(start, destination);
        return distance[destination];
    }

};

int main () {
    int cases; cin >> cases;
    for (int i = 0; i < cases; i++) {
        int nComputers, edges, origin, destination; cin >> nComputers >> edges >> origin >> destination;
        Graph servers(nComputers);
        
        while(edges--) {
            int i, j, weight; cin >> i >> j >> weight;
            servers.setEdge(i, j, weight);
            servers.setEdge(j, i, weight);
        }
        int distance = servers.getDistance(origin, destination);
        cout << "Case #" << i+1 << ": ";
        if(distance != INT_MAX) cout << distance << endl;
        else cout << "unreachable" << endl;
    }
    return 0;
} // g++ Sending\ email.cpp -o SE && ./SE < input.in > output.out
