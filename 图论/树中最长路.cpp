#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#define INF 0x7fffffff
using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

struct Edge {
    int v, next;
} e[N * 2];
int head[N], tot, ans;

void add_edge(int u, int v) {
    e[tot].v = v;
    e[tot].next = head[u];
    head[u] = tot++;
}
int dfs(int st, int pre) {
    int first = 0, second = 0;
    for(int i = head[st]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(v == pre) continue ;
        int d = dfs(v, st) + 1;
        if(d > first) {
            second = first;
            first = d;
        } else if(d > second) {
            second = d;
        }
    }
    if(first + second > ans) {
        ans = first + second;
    }
    return first;
}
int main() {
    int n, m, T;
    scanf("%d", &T);
    while(T--) {
        tot = 0;
        ans = 0;
        memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n - 1; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            add_edge(x - 1, y - 1);
            add_edge(y - 1, x - 1);
        }
        dfs(0, 0);
        printf("%d\n",ans);
    }
    return 0;
}
