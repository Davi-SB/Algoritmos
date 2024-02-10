#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topologicalSort(vector<vector<int>>& graph, vector<int>& indegree) {
    int n = graph.size();
    vector<int> result;
    priority_queue<int, vector<int>, greater<int>> pq;

    // Inicializa a fila de prioridade com nos de grau de entrada zero
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();
        result.push_back(node);

        // Atualiza o grau de entrada dos nos adjacentes e adiciona aqueles com grau zero à fila de prioridade
        for (int neighbor : graph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }

    // Verifica se todos os nos foram visitados (se não, há um ciclo)
    if (result.size() != n) {
        result.clear(); // Limpa o resultado para indicar que não há uma ordenação topológica válida
    }

    return result;
}

int main() {
    int n, m;
    cout << "Digite o numero de nos e o numero de arestas: ";
    cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);

    cout << "Digite as arestas (u v):" << endl;
    for (int i = 0; i < m; ++i) { // setEdges
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        indegree[v]++;
    }

    vector<int> result = topologicalSort(graph, indegree);

    if (result.empty()) {
        cout << "O grafo contem um ciclo. Nao e possivel realizar uma ordenacao topologica valida." << endl;
    } else {
        cout << "Ordenacao topologica com prioridade para nos de menor indice em caso de empate:" << endl;
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

 // g++ KahnGPT.cpp -o kahn && ./kahn < input2.in