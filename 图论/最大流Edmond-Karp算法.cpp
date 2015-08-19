#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;
const int INF = 1e7;
const int MOD = 1e9 + 7;
const int N = 200 + 10;

//下标从0开始
int n, m;
int G[N][N], vis[N], pre[N];

int bfs(int s, int t) {
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    int minEdge = INF;
    queue <int> Q;
    Q.push(s);
    vis[s] = 1;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int v = 0; v < n; v++) {
            if(!vis[v] && G[u][v]) {
                vis[v] = 1;
                minEdge = min(G[u][v], minEdge);
                pre[v] = u;
                if(v == t) return minEdge;
                Q.push(v);
            }
        }
    }
    return 0;
}
int Edmonds_Karp(int s, int t) {
    int max_flow = 0;
    int flow = 0;
    while(flow = bfs(s, t)) {
        max_flow  += flow;
        int u = t;
        while(pre[u] != -1) {
            G[pre[u]][u] -= flow;
            G[u][pre[u]] += flow;
            u = pre[u];
        }
    }
    return max_flow ;
}

int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    while(scanf("%d%d", &m, &n) != EOF) {
        memset(G, 0, sizeof(G));
        int x, y, cap;
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &cap);
            G[x - 1][y - 1] += cap;
        }
        printf("%d\n", Edmonds_Karp(0, n - 1));
    }
    return 0;
}
