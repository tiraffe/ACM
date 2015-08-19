#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

typedef long long LL;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Edge {
    int from, to, cap, flow, cost;
    Edge(int u, int v, int c, int f, int w) : from(u), to(v), cap(c), flow(f), cost(w) {}
};
struct MinCostFlow { // 点的下标从0开始
    const int MAXN = 1000 + 10;
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool inq[MAXN]; // 是否在队列中
    int d[MAXN]; // 从起点到i的距离
    int p[MAXN]; // 上一条弧
    int a[MAXN]; // 可改进量

    void init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int &flow, int& cost) {
        for(int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0, inq[s] = 1, p[s] = 0, a[s] = INF;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front();
            Q.pop();
            inq[u] = 0;
            for(int i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if(d[t] == INF) return false;
        flow += a[t];
        cost += d[t] * a[t];
        int u = t;
        while(u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
            u = edges[p[u]].from;
        }
        return true;
    }
    int Mincost(int s, int t) {
        int flow = 0, cost = 0;
        while(BellmanFord(s, t, flow, cost));
        return cost;
    }
} solve;

int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    int T, n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        solve.init(n + 2);
        int s = 0;
        int t = n + 1;
        int u, v, c;
        while (m--) {
            scanf("%d%d%d", &u, &v, &c);
            solve.AddEdge(u, v , 1 , c);
            solve.AddEdge(v, u , 1 , c);
        }
        solve.AddEdge(s, 1, 2, 0);
        solve.AddEdge(n, t, 2, 0);
        int ans = solve.Mincost(s, t);
        printf("%d\n", ans);
    }
    return 0;
}
