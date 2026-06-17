#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 99999;
struct Edge {
    int u, v, w;
};
bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}
int findRoot(int x, int parent[]) {
    while (x != parent[x]) x = parent[x];
    return x;
}
void Prim(int graph[][7], int n, int start) {
    int key[7], parent[7];
    bool visited[7] = { false };
    for (int i = 1; i <= n; i++) {
        key[i] = INF;
        parent[i] = -1;
    }
    key[start] = 0;
    int sum = 0;
    cout << "Prim算法最小生成树：" << endl;
    for (int k = 1; k <= n; k++) {
        int u = -1, minValue = INF;
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && key[i] < minValue) {
                minValue = key[i];
                u = i;
            }
        }
        visited[u] = true;
        if (parent[u] != -1) {
            cout << parent[u] << " - " << u << " 权值：" << key[u] << endl;
            sum += key[u];
        }
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    cout << "总权值：" << sum << endl;
}
void Kruskal(Edge edges[], int edgeNum, int n) {
    sort(edges, edges + edgeNum, cmp);
    int parent[7];
    for (int i = 1; i <= n; i++) parent[i] = i;
    int count = 0, sum = 0;
    cout << "Kruskal算法最小生成树：" << endl;
    for (int i = 0; i < edgeNum; i++) {
        int x = findRoot(edges[i].u, parent);
        int y = findRoot(edges[i].v, parent);
        if (x != y) {
            parent[x] = y;
            cout << edges[i].u << " - " << edges[i].v << " 权值：" << edges[i].w << endl;
            sum += edges[i].w;
            count++;
        }
        if (count == n - 1) break;
    }
    cout << "总权值：" << sum << endl;
}
int main() {
    int n = 6;
    Edge edges[10] = {
        {1,2,10},
        {1,4,30},
        {1,5,45},
        {2,3,50},
        {2,5,40},
        {2,6,25},
        {3,5,35},
        {3,6,15},
        {4,6,20},
        {5,6,55}
    };
    int graph[7][7];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
    for (int i = 0; i < 10; i++) {
        graph[edges[i].u][edges[i].v] = edges[i].w;
        graph[edges[i].v][edges[i].u] = edges[i].w;
    }
    Prim(graph, n, 1);
    cout << endl;
    Kruskal(edges, 10, n);
    return 0;
}