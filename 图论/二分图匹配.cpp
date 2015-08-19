/**
    ���ƥ���������ƥ���ƥ��ߵ���Ŀ
    ��С�㸲������ѡȡ���ٵĵ㣬ʹ����һ����������һ���˵㱻ѡ��
    ����������ѡȡ���ĵ㣬ʹ������ѡ�����������
    ��С·��������������һ�� DAG�������޻�ͼ����ѡȡ������·����ʹ��ÿ�����������ҽ�����һ��·����·��������Ϊ 0���������㣩��
    ����1�����ƥ���� = ��С�㸲���������� Konig ����
    ����2���������� = ������ - ���ƥ����
    ����3����С·�������� = ������ - ���ƥ����
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
