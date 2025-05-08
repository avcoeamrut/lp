#include <iostream>
#include <vector>
#include <queue>
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

    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v;

            #pragma omp critical
            {
                if (!q.empty()) {
                    v = q.front();
                    q.pop();
                    cout << v << " ";
                } else {
                    return;
                }
            }

            #pragma omp parallel for
            for (int i = 0; i < adj[v].size(); ++i) {
                int n = adj[v][i];

                #pragma omp critical
                {
                    if (!visited[n]) {
                        visited[n] = true;
                        q.push(n);
                    }
                }
}
}
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
cout << "Parallel BFS: ";
g.parallelBFS(0);
cout << endl;
return 0;
 }

/*
#include<iostream>
#include<queue>
#include<vector>
#include<omp.h>
using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;
    
    public:
    Graph(int V):V(V), adj(V){}

    void addEdge(int v, int w){
        adj[v].push_back(w);
    }

    void paralleBFS(int startvertex){
        
        vector<bool> visited(V,false);
        queue<int>q;
        visited[startvertex]=true;
        q.push(startvertex);
        while(!q.empty()){
            int v;
            #pragma omp critical
            if(!q.empty()){
                v=q.front();
                cout << v << " ";
                q.pop();
            }else{
                return;
            }

            #pragma omp parallel for
            for(int i=0;i<adj[v].size();++i){
                int n=adj[v][i];
                
                #pragma omp critical
                if(!visited[n]){
                    q.push(n);
                    visited[n]=true;
                }
            }
        }
    }
};

int main(){
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.paralleBFS(0);
    return 0;
}
   */ 