#include <time.h>
#define MAX 1010
bool adj[MAX][MAX];
int n, ar[MAX][MAX];
const int MOD = 1073750017;
int expo(long long x, int n){
    long long res = 1;

    while (n){
        if (n & 1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }

    return (res % MOD);
}
int rank(int n){ /// hash = 646599
    long long inv;
    int i, j, k, u, v, x, r = 0, T[MAX];

    for (j = 0; j < n; j++){
        for (k = r; k < n && !ar[k][j]; k++){}
        if (k == n) continue;

        inv = expo(ar[k][j], MOD - 2);
        for (i = 0; i < n; i++){
            x = ar[k][i];
            ar[k][i] = ar[r][i];
            ar[r][i] = (inv * x) % MOD;
        }

        for (u = r + 1; u < n; u++){
            if (ar[u][j]){
                for (v = j + 1; v < n; v++){
                    if (ar[r][v]){
                        ar[u][v] = ar[u][v] - (((long long)ar[r][v] * ar[u][j]) % MOD);
                        if (ar[u][v] < 0) ar[u][v] += MOD;
                    }
                }
            }
        }
        r++;
    }

    return r;
}
int tutte(int n){
    int i, j;
    srand(time(0));

    clr(ar);
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n; j++){
            if (adj[i][j]){
                unsigned int x = (rand() << 15) ^ rand();
                x = (x % (MOD - 1)) + 1;
                ar[i][j] = x, ar[j][i] = MOD - x;
            }
        }
    }

    return (rank(n) >> 1);
}
int main(){
    int T = 0, t, m, i, j, a, b;

    scanf("%d", &t);
    while (t--){
        clr(adj);
        scanf("%d %d", &n, &m);
        while (m--){
            scanf("%d %d", &a, &b);
            a--, b--;
            adj[a][b] = adj[b][a] = true;
        }

        printf("Case %d: %d\n", ++T, tutte(n));
    }
    return 0;
}