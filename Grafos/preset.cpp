#include <iostream>
#include <queue>
using namespace std;

class Graph {
private:
public:
};

int main() {



    return 0;
}































































// matrix
/*
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

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    int first(int currNode) {
        for (int i = 0; i < numNodes; i++) {
            if(matrix[currNode][i] != 0) return i; // nao ausencia
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o  vertice W
        for (int i = (w+1); i < numNodes; i++) {
            if(matrix[currNode][i] != 0) return i; // nao ausencia
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

    void setEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(matrix[i][j] == 0) numEdges++; // ausencia
        matrix[i][j] = 1;
    }

    void delEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(matrix[i][j] != 0) numEdges--; // nao ausencia
        matrix[i][j] = 0; // ausencia
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
};
*/

// matriz menor caminhho
/*
#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {
private:
    int** matrix;
    int* mark;
    int* distance;
    int numEdges, numNodes;

    void pVerify(int *p)  { 
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); } 
    }

    void pVerify(int **p) {
        if(p == nullptr) { cerr << "memory error" << endl; exit(1); }
    }

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    int first(int currNode) {
        for (int i = 0; i < numNodes; i++) {
            if(matrix[currNode][i] == 1) return i; // ausencia
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o  vertice W
        for (int i = (w+1); i < numNodes; i++) {
            if(matrix[currNode][i] == 1) return i; // ausencia
        }
        return numNodes;
    }

    void setMark(int currNode, int state) { 
        mark[currNode] = state;
    }
    
    int getMark(int currNode) {
        if(mark[currNode] == 0) return 0;
        return 1;
    }

    //void preVisit(int currNode) { cout << currNode << "  "; }

    //void posVisit(int currNode) { return; }

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
                nextNode = next(currNode, nextNode);
            }
        }
    }

public:
    Graph(int size) {
        this->matrix = new int*[size]; pVerify(matrix);
        for (int i = 0; i < size; i++) {
            this->matrix[i] = new int[size]; pVerify(matrix[i]);
        }
        this->mark = new int[size];
        this->distance = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
    }
    ~Graph() {
        for (int i = 0; i < numNodes; i++) delete[] matrix[i];
        delete[] matrix;
        delete[] mark;
        delete[] distance;
    }

    void setEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(matrix[i][j] == 0) numEdges++; // ausencia
        matrix[i][j] = 1; 
    }

    void delEdge(int i, int j) {
        checkNode(i); checkNode(j);
        if(matrix[i][j] != 0) numEdges--; // ausencia
        matrix[i][j] = 0; // ausencia
    }

    int* MinDistances(int start) {
        checkNode(start);
        for(int i = 0; i < numNodes; i++){
            setMark(i, 0); // UNVISITED para esse caso
            distance[i] = -1;
        } 

        BFSDistance(start);
        // desse ponto, distance[i] == -1 significa que nao ha como sair de start e chegar em i
        return distance;
    }
};
*/

// lista
/*
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
        cout << s.top() << "  "; s.pop();
    } cout << endl;

    return 0;
} // g++ Grafo_ListaAdjacencia.cpp -o G && ./G < inputLA.in
*/

// lista menor caminho
/*
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
    int* distance;
    int numEdges, numNodes;
    const int UNVISITED = 0, VISITED = 1;

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
                nextNode = next(currNode, nextNode);
            }
        }
    }

public:
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark = new int[size];
        this->distance = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
        delete[] this->distance;
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
*/
