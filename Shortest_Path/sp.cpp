#include <iostream>
#include <vector>
using namespace std;
#include <chrono>
using namespace chrono;
#define inf 142857

vector<int> dijkstra(int n, int s, vector<vector<int>>& adj) {
    vector<int> d(n + 1, inf);
    vector<bool> visited(n + 1, false);
    d[s] = 0;
    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || d[j] < d[u])) {
                u = j;
            }
        }
        visited[u] = true;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && adj[u][v] != inf) {
                if (d[v] > d[u] + adj[u][v])
                    d[v] = d[u] + adj[u][v];
            }
        }
    }
    return d;
}

vector<int> bellmanFord(int n, int s, vector<vector<int>>& adj, bool& hasNegativeCycle) {
    vector<int> d(n + 1, inf);
    d[s] = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                if (adj[u][v] != inf && d[u] != inf) {
                    if (d[v] > d[u] + adj[u][v]) {
                        d[v] = d[u] + adj[u][v];
                    }
                }
            }
        }
    }
    hasNegativeCycle = false;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] != inf && d[u] != inf) {
                if (d[v] > d[u] + adj[u][v]) {
                    hasNegativeCycle = true;
                    return d;
                }
            }
        }
    }
    return d;
}

int main() {
    int n = 6;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1));
    //假设以1为起点
    int s = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            adj[i][j] = inf;
    adj[1][2] = 10; adj[2][1] = 10;
    adj[1][4] = 30; adj[4][1] = 30;
    adj[1][5] = 45; adj[5][1] = 45;
    adj[2][3] = 50; adj[3][2] = 50;
    adj[2][5] = 40; adj[5][2] = 40;
    adj[2][6] = 25; adj[6][2] = 25;
    adj[3][5] = 35; adj[5][3] = 35;
    adj[3][6] = 15; adj[6][3] = 15;
    adj[4][6] = 20; adj[6][4] = 20;
    adj[5][6] = 55; adj[6][5] = 55;

    bool hasNegativeCycle;
    vector<int> d1 = dijkstra(n, s, adj);
    vector<int> d2 = bellmanFord(n, s, adj, hasNegativeCycle);

    cout << "顶点\tDijkstra\tBellman-Ford" << endl;
    for (int i = 1; i <= n; i++)
        cout << i << "\t" << d1[i] << "\t\t" << d2[i] << endl;
    if (hasNegativeCycle) {
        cout << "图中存在从源点可达的负权回路" << endl;
        return 0;
    }
    int repeat = 100000;
    volatile long long checksum = 0;
    auto start1 = steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        vector<int> d = dijkstra(n, s, adj);
        checksum += d[n];
    }
    auto end1 = steady_clock::now();
    auto start2 = steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        bool flag;
        vector<int> d = bellmanFord(n, s, adj, flag);
        checksum += d[n];
    }
    auto end2 = steady_clock::now();
    double time1 = duration<double, nano>(end1 - start1).count() / repeat;
    double time2 = duration<double, nano>(end2 - start2).count() / repeat;
    cout << endl;
    cout << "重复运行次数：" << repeat << endl;
    cout << "Dijkstra平均运行时间：" << time1 << " ns" << endl;
    cout << "Bellman-Ford平均运行时间：" << time2 << " ns" << endl;
    if (time1 < time2)
        cout << "Dijkstra运行速度更快，约为Bellman-Ford的 "
        << time2 / time1 << " 倍" << endl;
    else
        cout << "Bellman-Ford运行速度更快，约为Dijkstra的 "
        << time1 / time2 << " 倍" << endl;
    return 0;
}