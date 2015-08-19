#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e5 + 5;

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

struct SparseTable {
    int p[N][20];
    int (*cp) (int, int);
    void build(int a[], int n, int (*f)(int, int)) {
        cp = f;
        for (int i = 1; i <= n; ++ i) p[i][0] = a[i];
        for(int j = 1; (1 << j) <= n; ++j)
            for(int i = 1; i + (1 << j) - 1 <= n; ++i)
                p[i][j] = f(p[i][j - 1], p[i + (1 << (j - 1))][j - 1]);
    }
    int get(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return cp(p[l][k], p[r - (1 << k) + 1][k]);
    }
} ac1, ac2, ac3;

int pt[N];
map<int, int> mp;
int a[N];

int main() {
    int n, Q;
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", a + i);
        map<int, int>::iterator f = mp.find(a[i]);
        if (f != mp.end()) pt[i] = f->second;
        mp[a[i]] = i;
    }
    ac1.build(a, n, min);
    ac2.build(a, n, max);
    ac3.build(pt, n, max);
    printf("Case #%d:\n", 1);
    while (Q --) {
        int res = 0, k;
        scanf("%d", &k);
        for(int i = 1; i + k - 1 <= n; ++i) {
            int l = ac1.get(i, i + k - 1), r = ac2.get(i, i + k - 1);
            int tp = ac3.get(i, i + k - 1);
            if(r - l + 1 != k || tp >= i)continue;
            ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}
