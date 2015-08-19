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

/******************   O(n^2) 打表求组合数   ******************/

int C[4000][4000];

void CombinTable(int n) {
    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}

/****************   O(n) 预处理逆元求组合数 ***************/

int Inv[100005], FacInv[100005], Fac[100005];

int Comb(int n, int m) {
    if (m < 0 || m > n) return 0;
    return Fac[n] * 1LL * FacInv[m] % MOD * FacInv[n - m] % MOD;
}
void PrepareInv(int n) {
    Inv[1] = 1;
    for (int i = 2; i <= n; ++ i) {
        Inv[i] = (MOD - MOD / i) * 1LL * Inv[MOD % i] % MOD;
    }
    Fac[0] = FacInv[0] = 1;
    for (int i = 1; i <= n; ++ i) {
        Fac[i] = Fac[i - 1] * 1LL * i % MOD;
        FacInv[i] = FacInv[i - 1] * 1LL * Inv[i] % MOD;
    }
}

/***************** O(logN) Lucas定理 *********************/

LL exp_mod(LL a, LL b, LL p) {
    LL res = 1;
    while(b != 0) {
        if(b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}
LL combin(LL a, LL b, LL p) {
    if(a < b)   return 0;
    if(a == b)  return 1;
    if(b > a - b)   b = a - b;
    LL ans = 1, ca = 1, cb = 1;
    for(LL i = 0; i < b; ++i) {
        ca = (ca * (a - i)) % p;
        cb = (cb * (b - i)) % p;
    }
    ans = (ca * exp_mod(cb, p - 2, p)) % p;
    return ans;
}
LL Lucas(int n, int m, int p) {
    LL ans = 1;
    while(n && m && ans) {
        ans = (ans * combin(n % p, m % p, p)) % p;
        n /= p;
        m /= p;
    }
    return ans;
}

int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    PrepareInv(1000);
    CombinTable(1000);
    for(int i = 0;i<1000;i++) {
        for(int j = 0; j <=i ;j++) {
            int A = C[i][j];
            int B = Comb(i, j);
            int L = Lucas(i, j, MOD);
            if(A == B && B == L) continue;
            printf("%d   %d   %d\n", A, B, L);
        }
    }
    return 0;
}
