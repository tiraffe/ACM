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

struct Trie {
    int ch[N][26];
    int val[N], tot;
    Trie() {
        memset(ch, 0, sizeof(ch));
        memset(val, 0, sizeof(val));
        tot = 1;
    }
    void insert(char *s, int v) {
        int n = strlen(s);
        int u = 0;
        for(int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if(!ch[u][c]) ch[u][c] = tot++;
            u = ch[u][c];
        }
        val[u] = v;
    }
    int find(char *s) {
        int n = strlen(s);
        int u = 0;
        for(int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if(!ch[u][c]) return 0;
            u = ch[u][c];
        }
        return val[u];
    }
};

Trie T;

int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    int n;
    char s[N];
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s;
        T.insert(s, 1);
    }
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> s;
        if(T.find(s))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
