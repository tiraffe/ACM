#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;
const int INF = 0x7fffffff;
const int N = 10000 + 10;
const int LOG = 20;

vector<int> G[N];
int parent[LOG][N];
int depth[N];

void dfs(int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for (int i = 0; i < G[v].size(); i++)
        if (G[v][i] != p) dfs(G[v][i], v, d + 1);
}
void init(int root, int V) {
    dfs(root, -1, 0);
    for (int k = 0; k + 1 < LOG; k++) {
        for (int v = 0; v < V; v++) {
            if (parent[k][v] < 0) parent[k + 1][v] = -1;
            else parent[k + 1][v] = parent[k][parent[k][v]];
        }
    }
}
int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < LOG; k++) {
        if ((depth[v] - depth[u]) >> k & 1)
            v = parent[k][v];
    }
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--) {
        if (parent[k][u] != parent[k][v]) {
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

bool isroot[N];

int main() {
#ifdef TYH
    freopen("in.txt", "r", stdin);
#endif // TYH
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int a, b;
        for(int i = 0; i < n; i++) {
            G[i].clear();
            isroot[i] = true;
        }
        for(int i = 0; i < n - 1; i++) {
            scanf("%d%d", &a, &b);
            a--, b--;
            G[a].push_back(b);
            G[b].push_back(a);
            isroot[b] = false;
        }
        int root = 0;
        for(int i = 0; i < n; i++) {
            if(isroot[i] == true) root = i;
        }
        init(root, n);
        scanf("%d%d", &a, &b);
        a--, b--;
        printf("%d\n", lca(a, b) + 1);
    }

    return 0;
}
