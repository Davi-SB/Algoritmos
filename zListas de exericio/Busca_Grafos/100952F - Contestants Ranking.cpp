#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <limits.h>
using namespace std;

// https://codeforces.com/problemset/gymProblem/100952/F

class Node {
private:
    friend class Graph;
    int index; // peso removido para essa questao
public:
    Node(int index) {
        this->index = index;
    }
    ~Node() {}
};

class Graph {
private:
    vector<Node>* graphList;
    int* mark;
    vector<pair<int, int>> distance; // <INDEX, DISTANCE>
    int numEdges, numNodes, MAXNodes;
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
        for(int i = 0; i < graphList[currNode].size()-1; i++) {
            if(graphList[currNode][i].index == w) {
                return graphList[currNode][i+1].index;
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
        distance[start].second = 0;

        while (!nodeQueue.empty()) {
            int currNode = nodeQueue.front(); 
            nodeQueue.pop();
            int nextNode = first(currNode);
cout << "NextNode fora: " << nextNode << endl;

            while (nextNode < numNodes) {
cout << "NUMNODES: " << this->numNodes << endl;
cout << endl << "CHEGOU AQUI" << endl; 
                if(getMark(nextNode) == 0) {
                    setMark(nextNode, 1);
                    // na primeira vez que eh visitado, eh possivel definir a menor das distancias
                    distance[nextNode].second = distance[currNode].second + 1; // dsitancia do atual + 1 (ele)
                    nodeQueue.push(nextNode);
                }
                nextNode = next(currNode, nextNode);
cout << "NextNode dentro: " << nextNode << endl;
            }
        }
    }

public:
    Graph(int size) {
        this->graphList = new vector<Node>[size];
        this->mark = new int[size];
        this->distance.resize(size);
        this->MAXNodes = size;
        this->numNodes = 0;
        this->numEdges = 0;
    }
    ~Graph() {
        delete[] this->graphList;
        delete[] this->mark;
    }


    void addNode() {
        this->numNodes++;
    }

    int getNumNodes() {
        return this->numNodes;
    }
 
    void setEdge(int a, int b) {
        checkNode(a); checkNode(b);
        Node temp1(b);
        graphList[a].push_back(temp1);
        numEdges++;

        Node temp2(a);
        graphList[b].push_back(temp2);
        numEdges++;
    }

    vector<pair<int, int>> MinDistances(int start) {
        checkNode(start);
        for(int i = 0; i < numNodes; i++) {
            setMark(i, 0); // UNVISITED para esse caso
            distance[i] = {i, INT_MAX};
        } 
        BFSDistance(start);
        // desse ponto, distance[i] == INT_MAX significa que nao ha como sair de start e chegar em i
        return distance;
    }
};

bool isInMap(map<string, int> hashTable, string line) {
    return hashTable.find(line) != hashTable.end();
}

int main () {
    int T; cin >> T;
    while(T--) {
        map<string, int> hashTable;
        map<int, string> hashVOLTA;
        Graph grafo(101*3); // pior caso do num maximo dado pela questao
        
        int numLines; cin >> numLines;
        while (numLines--) {
            string line[3];

            for(int i=0; i<3; i++) {
                cin >> line[i];
                if(!isInMap(hashTable, line[i])) {
                    // a key associada ao nome eh o indice desse nome no grafo
                    hashTable[line[i]] = grafo.getNumNodes(); // string --> int
                    hashVOLTA[grafo.getNumNodes()] =  line[i]; // int --> string
                    grafo.addNode();
                }
            }
            
                        // Iterando sobre todos os elementos do map
                        cout << "Todos os elementos do hashTable:" << endl;
                        for (pair<string, int> par : hashTable) {
                            cout << par.first << ": " << par.second << endl;
                        }

                        // Iterando sobre todos os elementos do map
                        cout << "Todos os elementos do hashVOLTA:" << endl;
                        for (pair<int, string> par : hashVOLTA) {
                            cout << par.first << ": " << par.second << endl;
                        }

            // obs: a implementacao ja insere arestas nao-direcionadas
            grafo.setEdge(hashTable[line[0]], hashTable[line[1]]);
            grafo.setEdge(hashTable[line[0]], hashTable[line[2]]);
            grafo.setEdge(hashTable[line[1]], hashTable[line[2]]);   

        }

        vector<pair<int, int>> distances = grafo.MinDistances(hashTable["Ahmad"]);   

                        cout << "Todos os elementos do distances:" << endl;
                        for (int W = 0; W < grafo.getNumNodes(); W++) cout << distances[W].first << ": " << distances[W].second << endl;

        // Ordenando parcialmente o vetor com base nos inteiros (segundo elemento do par)
        sort(distances.begin(), distances.begin() + grafo.getNumNodes(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

                        cout << "Todos os elementos do distances ORDENADO:" << endl;
                        for (int W = 0; W < grafo.getNumNodes(); W++) cout << distances[W].first << ": " << distances[W].second << endl;
       
        cout << grafo.getNumNodes() << endl;
        for (int i=0; i < grafo.getNumNodes(); i++) {
            if(distances[i].second != INT_MAX) cout << hashVOLTA[distances[i].first] << ' ' << distances[i].second << endl;
            else cout << hashVOLTA[distances[i].first] << ' ' << "undefined" << endl;
        }

    }

    return 0;
} // g++ 100952F\ -\ Contestants\ Ranking.cpp -o G && ./G < inputsample.in