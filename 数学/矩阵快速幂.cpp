#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF = 0x7fffffff;
const int N = 100 + 10;
const int MOD = 1e9 + 7;

struct Matrix {
    int n , m;
    LL a[N][N];
    Matrix (int _n , int _m) {
        n = _n , m = _m;
        memset(a , 0 , sizeof(a));
    }
    LL* operator [] (int x) {
        return a[x];
    }
    const LL* operator [] (int x) const {
        return a[x];
    }
};
Matrix operator * (const Matrix& A , const Matrix& B) {
    Matrix res(A.n , B.m);
    for (int i = 0 ; i < A.n ; ++ i) {
        for (int j = 0 ; j < A.m ; ++ j) {
            if(!A[i][j]) continue;
            for (int k = 0 ; k < B.m ; ++ k) {
                res[i][k] += A[i][j] * B[j][k] % MOD;
                res[i][k] %= MOD;
            }
        }
    }
    return res;
}
Matrix operator ^ (Matrix& A , int x) {
    int n = A.n;
    Matrix E(n, n);
    for(int i = 0; i < n; i++) E[i][i] = 1;
    for (; x; x >>= 1) {
        if (x & 1)
            E = E * A;
        A = A * A;
    }
    return E;
}
int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    int n, d, x;
    Matrix A(101, 101);
    A[100][0] = A[100][100] = 1;
    scanf("%d%d", &n, &x);
    for(int i = 0; i < n; i++) {
        scanf("%d", &d);
        A[d - 1][0]++;
    }
    for(int i = 1; i < 100; i++) {
        A[i - 1][i] = 1;
    }
    A = A ^ x;
    printf("%d\n", (A[0][0] + A[100][0]) % MOD);
    return 0;
}
