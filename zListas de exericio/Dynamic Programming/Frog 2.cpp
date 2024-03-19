#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
using namespace std;

// SOLVED - https://vjudge.net/problem/AtCoder-dp_b

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

    void setEdge(int a, int b, int weight) {
        Node temp(b, weight);
        graphList[a].push_back(temp);
        numEdges++;
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

    int getDistance(int start, int destination) {
        dijkstra(start, destination);
        return distance[destination];
    }

};

int main() {
    int N, varMax; cin >> N >> varMax;
    int temp;
    vector<int> height;
    while(cin >> temp) height.push_back(temp);

    Graph G(N);
    // for(int i=0; i < N-1; i++) G.setEdge(i, i+1, abs(height[i] - height[i-1]));
    for(int i=0; i < N-1; i++) {
        for(int j=1; j < varMax+1; j++) {
            if((i+j) > (N-1)) break;
            G.setEdge(i, i+j, abs(height[i] - height[i+j]));
        }
    }
    cout << G.getDistance(0, N-1);
    return 0;
}