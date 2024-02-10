#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// SOLVED - https://www.spoj.com/problems/TOPOSORT/

class Graph {
private:
    vector<int>* graphList;
    int *preRequisito;
    int numNodes; 
public:
    Graph (int numN) {
        this->graphList = new vector<int>[numN];
        this->numNodes = numN;
        this->preRequisito = new int[numN];
        for (int i = 0; i < numN; ++i) this->preRequisito[i] = 0;
    } 
    ~Graph () {
        delete[] graphList;
        delete[] preRequisito;
    }

    void setEdge(int a, int b) {
        graphList[a].push_back(b);
        preRequisito[b]++;
    }

    void toposort() {
        priority_queue< int, vector<int>, greater<int> > pQueue; // tipo do elemento, estrutura de dado da fila e criterio de ordenacao
        vector<int> toposort;

        for (int i = 0; i < numNodes; ++i) { // push de nodes sem prerequisitos
            if (!preRequisito[i]) pQueue.push(i);
        }

        while (!pQueue.empty()) {
            int currNode = pQueue.top(); pQueue.pop();
            toposort.push_back(currNode); // node passa da fila para o resultado do toposort

            for (int i = 0; i < (int)graphList[currNode].size(); i++) {
                preRequisito[graphList[currNode][i]]--;
                if (!preRequisito[graphList[currNode][i]]) {
                    pQueue.push(graphList[currNode][i]);
                }
            }
        }

        if (toposort.size() == numNodes) { // caso sucedido
            for (int i = 0; i < (int)toposort.size(); i++) {
                cout << toposort[i]+1 << " ";
            } cout << endl;
        }
        else cout << "Sandro fails." << endl; // nao foi possivel passar por todos os nos, fazer todas as tarefas
    }
}; 

int main() {
    int n, m; cin >> n >> m;
    Graph grafo(n); 

    while(m--) { 
        int a, b; cin >> a >> b;
        a--; b--; 
        grafo.setEdge(a, b);    
    }
    grafo.toposort();
    return 0;
}