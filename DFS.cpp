#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

 public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);

        #pragma omp parallel
        {
            #pragma omp single
            parallelDFSUtil(startVertex, visited);
        }
    }

    void parallelDFSUtil(int v, vector<bool>& visited) {
        #pragma omp critical
        {
            if (visited[v]) return;
            visited[v] = true;
            cout << v << " ";
        }

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int n = adj[v][i];

            #pragma omp critical
            {
                if (!visited[n]) {
                    #pragma omp task
                    parallelDFSUtil(n, visited);
                }
            }
        }

        #pragma omp taskwait
    }
 };

 int main() {
    Graph g(7);    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    cout << "Parallel DFS: ";
    g.parallelDFS(0);
    cout << endl;
    return 0;
 }