#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 1e5 + 10;
const int INF = 1 << 30;

struct Edge {
    int from, to, cap, flow;
};
struct ISAP {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[maxn];   // �ڽӱ�G[i][j]��ʾ���i�ĵ�j������e�����е����
    bool vis[maxn];        // BFSʹ��
    int d[maxn];           // ����㵽i�ľ���
    int cur[maxn];        // ��ǰ��ָ��
    int p[maxn];          // ������·�ϵ���һ����
    int num[maxn];        // �����ż���

    void AddEdge(int from, int to, int cap) {
        edges.push_back((Edge) {
            from, to, cap, 0
        });
        edges.push_back((Edge) {
            to, from, 0, 0
        });
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = 1;
        d[t] = 0;
        while(!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i] ^ 1];
                if(!vis[e.from] && e.cap > e.flow) {
                    vis[e.from] = 1;
                    d[e.from] = d[x] + 1;
                    Q.push(e.from);
                }
            }
        }
        return vis[s];
    }
    void init(int n) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    int Augment() {
        int x = t, a = INF;
        while(x != s) {
            Edge& e = edges[p[x]];
            a = min(a, e.cap - e.flow);
            x = edges[p[x]].from;
        }
        x = t;
        while(x != s) {
            edges[p[x]].flow += a;
            edges[p[x] ^ 1].flow -= a;
            x = edges[p[x]].from;
        }
        return a;
    }

    int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for(int i = 0; i < n; i++) num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while(d[s] < n) {
            if(x == t) {
                flow += Augment();
                x = s;
            }
            int ok = 0;
            for(int i = cur[x]; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if(e.cap > e.flow && d[x] == d[e.to] + 1) { // Advance
                    ok = 1;
                    p[e.to] = G[x][i];
                    cur[x] = i; // ע��
                    x = e.to;
                    break;
                }
            }
            if(!ok) { // Retreat
                int m = n - 1; // ��ֵע��
                for(int i = 0; i < G[x].size(); i++) {
                    Edge& e = edges[G[x][i]];
                    if(e.cap > e.flow) m = min(m, d[e.to]);
                }
                if(--num[d[x]] == 0) break;
                num[d[x] = m + 1]++;
                cur[x] = 0; // ע��
                if(x != s) x = edges[p[x]].from;
            }
        }
        return flow;
    }
};


ISAP solve;
int n, m, s, t;

int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        int x, y;
        int wst = -INF, est = INF;
        solve.init(n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            if(wst <= x) wst = x, t = i;
            if(est >= x) est = x, s = i;
        }
        int w;
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &w);
            x--, y--;
            solve.AddEdge(x, y, w);
            solve.AddEdge(y, x, w);
        }
        int ans = solve.Maxflow(s, t);
        printf("%d\n", ans);
    }
    return 0;
}
