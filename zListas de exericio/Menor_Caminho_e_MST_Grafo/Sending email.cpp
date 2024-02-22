#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <set>
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
    int numEdges, numNodes;
    const bool VISITED = true;

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    bool checkNodeIgnore(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) return true;
        return false;
    }

    Node first(int currNode) {
        if(!graphList[currNode].empty()) return graphList[currNode][0];
        return Node(numNodes, numNodes);
    }

    Node next(int currNode, int w) { // primeiro em que V se liga apos o vertice W
        if(w+1 < graphList[currNode].size()) return graphList[currNode][w+1];
        return Node(numNodes, numNodes);
    }

    void dijkstra(int start) {
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
            parent[t.curr] = t.prev;

            Node n = first(t.curr);
            while(n.index < numNodes) {
                if(distance[n.index] > (distance[t.curr] + n.weight) && (mark[n.index] == !VISITED)) {
                    distance[n.index] = distance[t.curr] + n.weight;
                    pq.push(Trio(t.curr, n.index, distance[n.index]));
                }
                n = next(t.curr, n.index);
                cout << "chegou" << endl;
            }
        }
    }

    vector<Node> removeRepeated(vector<Node> vec) {
        set<Node> newSet;
        vector<Node> resultado;
        for (Node elemento : vec) {
            if (newSet.find(elemento) == newSet.end()) {
                newSet.insert(elemento);
                resultado.push_back(elemento);
            }
        }
        return resultado;
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
        if (checkNodeIgnore(a) || checkNodeIgnore(b)) return;
        Node temp(b, weight);
        graphList[a].push_back(temp);
        numEdges++;
    }

    void reduceGraph() {
        for (int i = 0; i < numNodes; i++) {
            graphList[i] = removeRepeated(graphList[i]);
        } 
    }

    int getDistance(int start, int destination) {
        dijkstra(start);
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
        // servers.reduceGraph();
        int distance = servers.getDistance(origin, destination);
        cout << "Case #" << i+1 << ": ";
        if(distance != INT_MAX) cout << distance << endl;
        else cout << "unreachable" << endl;
    }
    return 0;
} // g++ Sending\ email.cpp -o SE && ./SE < input.in > output.out
