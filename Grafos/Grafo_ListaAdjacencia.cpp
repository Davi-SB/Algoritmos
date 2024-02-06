#include <iostream>
#include <queue>
#include <list>
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
    //friend class Node;
    list<Node>* graphList;
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
        if(!graphList[currNode].empty()) {
            Node temp = graphList[currNode].front();
            return temp.index;
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o  vertice W
        bool found = false;
        auto it = graphList[currNode].begin();
        
        for(; (it != graphList[currNode].end()) && (!found); it++) {
            if(it->index == w) found = true;
        }
        if(!found) return numNodes; // saiu do for pq acabou a linked list e nao pq w foi encontrado

        it++; // next()
        if(it != graphList[currNode].end()) return it->index;
        return numNodes;
    }

    void setMark(int currNode, int state) { 
        mark[currNode] = state;
    }
    
    bool getMark(int currNode) {
        if(mark[currNode] == UNVISITED) return false;
        return true;
    }

    void preVisit(int currNode) { currNode++; return; } // FAZ NADA

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

public:
    Graph(int size) {
        this->graphList = new list<Node>[size];
        this->mark = new int[size];
        this->numNodes = size;
        this->numEdges = 0;
    }
    ~Graph() {
        for (int i = 0; i < (numNodes-1); i++) this->graphList[i].clear();
        delete[] this->graphList;
        delete[] this->mark;
    }

    void setEdge(int i, int j, int weight) {
        //if(weight == 0) { cerr << "peso nulo"; exit(1); } // ???????????????

        auto it = graphList[i].begin();
        bool found = false;

        for(; (it != graphList[i].end()) && (!found); it++) {
            if(it->index > j) found = true;
        }
        
        if(it != graphList[i].begin()) it--; // volta para a posicao certa para inserir 
        
        if((!graphList[i].empty()) && (it->index == j)) { // caso a aresta ja exista, apenas atualiza o peso
            it->weight = weight;
        }
        else {
            Node temp(j, weight);
            graphList[i].insert(it, temp);
            numEdges++;
        }
    }

    void delEdge(int i, int j) {
        if(graphList[i].empty()) return;

        auto it = graphList[i].begin();
        bool found = false;

        for(; (it != graphList[i].end()) && (!found); it++) {
            if(it->index == j) found = true;
        }

        if(found) {
            //if(it != graphList[i].begin()) 
            it--;
            graphList[i].erase(it);
            numEdges--;
        }
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