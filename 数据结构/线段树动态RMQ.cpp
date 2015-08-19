#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
const int INF = 0x7fffffff;
const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

int n, m;

/// RMQ线段树
/// 插入区间:[0,n-1]  查询:[l,r]
struct SegmTree {
    int *Tree;
    int n;
    SegmTree(int SIZE = N) {
        n = SIZE;
        Tree = new int[SIZE * 4];
    }
    void ins(int pos, int val) {
        update(pos, val, 0, n - 1, 1);
    }
    int get(int l, int r) { // [l,r]
        return query(l, r, 0, n - 1, 1);
    }

private:
    void update(int pos, int val, int l, int r, int rt) {
        if (l == r) {
            Tree[rt] = val;
            return ;
        }
        int m = (l + r) >> 1;
        if (pos <= m) update(pos , val , l , m , rt << 1);
        else update(pos , val , m + 1 , r , rt << 1 | 1);
        Tree[rt] = max(Tree[rt << 1] , Tree[rt << 1 | 1]);
    }
    int query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return Tree[rt];
        }
        int m = (l + r) >> 1;
        int ret = -INF;
        if (L <= m) ret = max(ret , query(L , R , l , m , rt << 1));
        if (R > m) ret = max(ret , query(L , R , m + 1 , r , rt << 1 | 1));
        return ret;
    }
};

SegmTree A, B;

int main() {
    int n, m;
    while(~scanf("%d%d", &n, &m)) {
        int x, l, r;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            A.ins(i, x);
            B.ins(i, -x);
        }
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &l, &r);
            l--, r--;
            printf("%d\n", A.get(l, r) + B.get(l, r));
        }
    }
}
