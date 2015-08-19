/**
    最大匹配数：最大匹配的匹配边的数目
    最小点覆盖数：选取最少的点，使任意一条边至少有一个端点被选择
    最大独立数：选取最多的点，使任意所选两点均不相连
    最小路径覆盖数：对于一个 DAG（有向无环图），选取最少条路径，使得每个顶点属于且仅属于一条路径。路径长可以为 0（即单个点）。
    定理1：最大匹配数 = 最小点覆盖数（这是 Konig 定理）
    定理2：最大独立数 = 顶点数 - 最大匹配数
    定理3：最小路径覆盖数 = 顶点数 - 最大匹配数
**/
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#define INF 0x7fffffff
using namespace std;

const int MOD = 1e9 + 7;
const int N = 100 + 10;
const int M = 300 + 10;

int n, m;
int vis[M], match[M];
int G[N][M];

bool dfs(int u) {
    for(int v = 0; v < m; v++) {
        if(vis[v] || !G[u][v]) continue;
        vis[v] = true;
        if(match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}
int maxmatch() {
    int cnt = 0;
    memset(match, -1, sizeof(match));
    for(int i = 0; i < n; i++) {
        memset(vis, false, sizeof(vis));
        if(dfs(i)) cnt++;
    }
    return cnt;
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        memset(G, 0, sizeof(G));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            int cnt, s;
            scanf("%d", &cnt);
            while(cnt--) {
                scanf("%d", &s);
                s--;
                G[i][s] = 1;
            }
        }
        int ans = maxmatch();
        if(ans == n) puts("YES");
        else puts("NO");
    }
    return 0;
}
