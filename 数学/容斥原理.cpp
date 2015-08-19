#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

typedef long long LL;
const int INF = 0x7fffffff;
const int MOD = 1e9 + 7;
const int N = 1e5 + 10;

vector <int> fac;

void getFac(int n) { // 分解质因数
    fac.clear();
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            fac.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) fac.push_back(n);
}
LL solve(LL x) { // 返回 [1, x] 与 p 互素的的个数
    int n = fac.size();
    LL ans = 0;
    for(int i = 0; i < (1 << n); i++) {
        int res = 1, sign = 1;
        for(int k = 0; k < n; k++) {
            if(i >> k & 1) {
                sign *= -1;
                res *= fac[k];
            }
        }
        ans += sign * (x / res);
    }
    return ans;
}
int main() {
#ifdef Tally_Ho
    freopen("in.txt", "r", stdin);
#endif // Tally_Ho
    int n, k;
    while(scanf("%d%d", &n, &k) != EOF) {
        getFac(n);
        LL left = 1, right = 1LL << 50, mid;
        while(right > left) {
            mid = (left + right) / 2;
            if(solve(mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        printf("%lld\n", left);
    }
    return 0;
}
