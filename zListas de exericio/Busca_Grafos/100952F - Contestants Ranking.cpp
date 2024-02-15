#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <set>
using namespace std;
#define endl '\n'

// SOLVED - https://codeforces.com/problemset/gymProblem/100952/F

class Graph {
private:
    vector<int>* graphList;
    int* mark;
    vector<pair<string, int>> distance; // <INDEX, DISTANCE>
    int numEdges, numNodes, MAXNodes;
    const int UNVISITED = 0, VISITED = 1;

    void checkNode(int nodeIndex) {
        if((nodeIndex < 0) || (nodeIndex >= this->numNodes)) { cerr << "node out of bounds - checkNode" << endl; exit(1); }
    }

    int first(int currNode) {
        if(!graphList[currNode].empty()) {
            return graphList[currNode][0];
        }
        return numNodes;
    }

    int next(int currNode, int w) { // primeiro em que V se liga apos o vertice W
        for(int i = 0; i < graphList[currNode].size()-1; i++) {
            if(graphList[currNode][i] == w) {
                return graphList[currNode][i+1];
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

            while (nextNode < numNodes) {
                if(getMark(nextNode) == 0) {
                    setMark(nextNode, 1);
                    // na primeira vez que eh visitado, eh possivel definir a menor das distancias
                    distance[nextNode].second = distance[currNode].second + 1; // dsitancia do atual + 1 (ele)
                    nodeQueue.push(nextNode);
                }
                nextNode = next(currNode, nextNode);
            }
        }
    }

public:
    Graph(int size) {
        this->graphList = new vector<int>[size];
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
        graphList[a].push_back(b);
        graphList[b].push_back(a);
    }

    vector<pair<string, int>> MinDistances(int start) {
        checkNode(start);
        for(int i = 0; i < numNodes; i++) {
            setMark(i, 0); // UNVISITED para esse caso
            distance[i].second = INT_MAX;
        } 
        BFSDistance(start);
        // desse ponto, distance[i] == INT_MAX significa que nao ha como sair de start e chegar em i
        return distance;
    }

    vector<int> removeRepeated(vector<int> vec) {
        set<int> newSet;
        vector<int> resultado;

        for (int elemento : vec) {
            if (newSet.find(elemento) == newSet.end()) {
                newSet.insert(elemento);
                resultado.push_back(elemento);
            }
        }
        return resultado;
    }

    void reduceGraph() {
        for (int i = 0; i < numNodes; i++) {
            graphList[i] = removeRepeated(graphList[i]);
        } 
    }
};

bool compare(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second != b.second) return a.second < b.second; // ordena por inteiros crescentes
    else return a.first < b.first; // desempate por string crescente
}

bool isInMap(unordered_map<string, int> hashTable, string line) {
    return hashTable.find(line) != hashTable.end();
}

int main () {
    int T; cin >> T;
    while(T--) {
        unordered_map<string, int> hashTable;
        unordered_map<int, string> hashVOLTA;
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
            
            // obs: a implementacao ja insere arestas nao-direcionadas
            grafo.setEdge(hashTable[line[0]], hashTable[line[1]]);
            grafo.setEdge(hashTable[line[0]], hashTable[line[2]]);
            grafo.setEdge(hashTable[line[1]], hashTable[line[2]]);   

        }

        grafo.reduceGraph();

        vector<pair<string, int>> distances = grafo.MinDistances(hashTable["Ahmad"]); // <name, distance>
        for (int i = 0; i < grafo.getNumNodes(); i++) distances[i].first = hashVOLTA[i]; // preenche o nome no par
        
        sort(distances.begin(), distances.begin() + grafo.getNumNodes(), compare);

        cout << grafo.getNumNodes() << endl;
        for (int i=0; i < grafo.getNumNodes(); i++) {
            if(distances[i].second != INT_MAX) cout << distances[i].first << ' ' << distances[i].second << endl;
            else cout << distances[i].first << " undefined" << endl;
        }
    }
    return 0;
} // g++ 100952F\ -\ Contestants\ Ranking.cpp -o GA && ./GA < input.in > output.out