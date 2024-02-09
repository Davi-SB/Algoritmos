#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    vector<int>* graphList;
    int *mark;
    int numEdges, numNodes; 
public:
    Graph (int numN) {
        this->graphList = new vector<int>[numN];
        this->mark = new int[numN];
        this-> numEdges = 0;
        this->numNodes = numN;
    } 
    ~Graph () {
        delete[] mark;
        delete[] graphList;
    }

    int first(int currNode) {
        if(!graphList[currNode].empty()) {
            return graphList[currNode][0];
        }   
        return numNodes;
    }

    int next(int currNode, int w) {
        for (int i = 0; i < graphList[currNode].size()-1; i++) {
            if(graphList[currNode][i] == w) {
                return graphList[currNode][i+1];
            }
        }
        return numNodes;
    }

    void setEdge(int a, int b) {
        graphList[a].push_back(b);
        numEdges++;
    }

    void DFS(int v) {
        //cout << v << endl;
        mark[v] = 1;
        int w = first(v);
        while(w < numNodes) {
            //cout << "loooop?" << endl;
            if(!mark[w]) DFS(w);
            w = next(v, w);
        }
    }

    int qtdConexos() {
        int count=0;
        for (int i = 0; i < numNodes; i++) mark[i] = 0;
        
        for (int i = 0; i < numNodes; i++) {
            if(!mark[i]) {
                DFS(i);
                count++;
            }
        }
        return count;
    }
}; 

int main() {
    int numTests; cin >> numTests;
    while(numTests--) {
        int qtdNodes, qtdArestas; cin >> qtdNodes >> qtdArestas;
        Graph grafo(qtdNodes);
        while (qtdArestas--) {
            //cout << "setEdge" << endl;
            int a, b; cin >> a >> b;
            grafo.setEdge(a, b);
            grafo.setEdge(b, a);  
        }
        cout << grafo.qtdConexos() << endl;
        //cout << "chegou" << endl;
    }
    return 0;
} // g++ EP.cpp -o EP && ./EP < input.in 
