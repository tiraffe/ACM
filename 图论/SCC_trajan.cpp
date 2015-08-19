#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long LL;
const int INF = 0x7fffffff;
const int MOD = 1e9 + 7;
const int N = 1e5 + 10;

vector <int> G[N];
int pre[N], lowlink[N], sccno[N], num[N], dfs_clock, scc_cnt;
stack <int> S;

void dfs(int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    S.push(u);
    for(itn i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[u]) {
            dfs(v);
        } else if(!sccno[v]) {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if(lowlink[u] == pre[u]) {
        scc_cnt++;
        for(;;) {
            int x = S.top();
            S.pop();
            sccno[x] = scc_cnt;
            num[scc_cnt]++;
            if(x == u) break;
        }
    }
}
void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    memset(num, 0, sizeof(num));
    for(itn i = 0; i < n; i++) {
        if(!pre[i]) dfs(i);
    }
}

int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    int T, cas;
    scanf("%d", &T);
    while(T--) {
        printf("Case %d : ", ++cas);
        scanf("%d%d", &n, &m);
        int x, y;
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            x--, y--;
            G[x].push_back(y);
        }
        find_scc();
        if(num[1] == n) {
            puts("0");
            continue;
        }
        for(int i = 0; i < n; i++) in0[i] = out0[i] = 1;
        for(int u = 0; u < n; u++) {
            for(int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                if(sccno[u] != sccno[v]) in0[sccno[v]] = out0[sccno[u]] = 0;
            }
        }
        int minv = INF;
        for(int i = 0; i < n; i++) {
            if(in0[i] == 0 || out0[i] == 0) minv = min(minv, num[i]);
        }
        int remv = n - minv;
        LL ans = 1LL * (minv - 1) * minv + (remv - 1) * remv + minv * remv - m;
        printf("%I64d\n", ans);
    }
    return 0;
}

