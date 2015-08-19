#include <cstdio>
#include <algorithm>
using namespace std;

double a[1010][510], b[1010], ans[510];
const double EPS = 0.0000001;
int n, m;

bool Guess() {
    int i, j, k;
    for(i = 1; i <= n; i++) {
        bool flag = false;
        for(j = i; j <= m; j++) if(a[j][i] > EPS || a[j][i] < -EPS) { //从第i行开始，找到第i列不等于0的行j
            for(k = i; k <= n; k++) swap(a[j][k], a[i][k]);
            swap(b[i], b[j]);
            flag = true;
            break;
        }
        if(!flag) {
            printf("Many solutions\n");
            return false;
        }
        for(j = i + 1; j <= m; j++) {
            double tt = a[j][i];
            for(k = i; k <= n; k++) a[j][k] -= a[i][k] * (tt / a[i][i]);
            b[j] -= b[i] * (tt / a[i][i]);
        }
    }

    for(i = 1; i <= m; i++) {
        bool flag = false;
        for(j = 1; j <= n; j++) if(a[i][j] > EPS || a[i][j] < -EPS) {
            flag = true;
            break;
        }
        if(!flag && (b[i] > EPS || b[i] < -EPS)) {
            printf("No solutions\n");
            return false;
        }
    }

    for(i = n; i >= 1; i--) {
        for(j = i + 1; j <= n; j++) {
            b[i] -= a[i][j] * ans[j];
            a[i][j] = 0;
        }
        ans[i] = b[i] / a[i][i];
    }
    return true;
}
int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for(i = 1; i <= m; i++) {
        for(j = 1; j <= n; j++) scanf("%lf", &a[i][j]);
        scanf("%lf", b + i);
    }
    if(Guess()){
        for(i = 1; i <= n; i++) printf("%d\n", (int)(ans[i] + 0.5));
    }
    return 0;
}
