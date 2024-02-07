#include <iostream>
#include <queue>
#include <stack>
#include <vector>
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

class Graph {
private:
    vector<Node>* graphList;
    int* mark;
    int numEdges, numNodes;
    const int UNVISITED = 0, VISITED = 1;
    
    void (Graph:: *traverse)(int v) = nullptr;
    stack<int> stackToposort;

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    int first(int currNode) {
        if(!graphList[currNode].empty()) {
            return graphList[currNode][0].index;
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o vertice W
        for(int i = 0; i < (int)graphList[currNode].size(); i++) {
            if(graphList[currNode][i].index == w) {
                if((i+1) < (int)graphList[currNode].size()) 
                    return graphList[currNode][i+1].index;
                else 
                    return numNodes;
            }
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

    void posVisit(int currNode) { currNode++; return; } // FAZ NADA

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

    void toposortHelp(int currNode) {
        setMark(currNode, VISITED);

        int nextNode = first(currNode);
        while(nextNode < numNodes) {
            if(getMark(nextNode) == UNVISITED) {
                toposortHelp(nextNode);
            }
            nextNode = next(currNode, nextNode);
        }

        this->stackToposort.push(currNode);
    }

public:
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
    }

    void setEdge(int a, int b, int weight) {
        checkNode(a); checkNode(b);
        //int i=0;
        //bool found = false;
        //for(; (i < graphList[a].size()) && (!found); i++) if(graphList[a][i].index == b) found = true;

        //if(!found) {
        Node temp(b, weight);
        graphList[a].push_back(temp);
        numEdges++;
        //}
        //else graphList[a][i].weight = weight;
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

    void graphTraverse(int v, char searchType) { // "DFS" or "BFS" expected // 
        checkNode(v);
        if(searchType == 'D') traverse = &Graph::DFS;
        else if(searchType == 'B') traverse = &Graph::BFS;
        else { cerr << "error searchType - graphTraverse" << endl; exit(1); }

        for(int i = 0; i < numNodes; i++) setMark(i, UNVISITED);

        for(int i = 0; i < numNodes; i++) {
            if(getMark(v) == UNVISITED) 
                (this->*traverse)(v);
        }
    }

    stack<int> toposort(int v) {
        checkNode(v);
        for(int i = 0; i < numNodes; i++) setMark(i, UNVISITED);

        for(int i = 0; i < numNodes; i++) {
            if(getMark(v) == UNVISITED) 
                toposortHelp(i);
        }

        return stackToposort;
    }
};

int main () {

    int n, m; cin >> n >> m;
    Graph g(n);

    int i, j;
    while(m--) {
        cin >> i >> j;
        g.setEdge(i, j, 1);
    }

    stack<int> s = g.toposort(0);

    while(!s.empty()) {
        cout << s.top() << "  ";
        s.pop();
    } cout << endl;

    return 0;
} // g++ Grafo_ListaAdjacencia.cpp -o G && ./G < inputLA.in