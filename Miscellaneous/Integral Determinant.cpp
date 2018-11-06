#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const long long MOD = 4517409488245517117LL;
const long double OP = (long double)1 / 4517409488245517117LL;

long long mul(long long a, long long b){
   long double res = a;
   res *= b;
   long long c = (long long)(res * OP);
   a *= b;
   a -= c * MOD;
   if (a >= MOD) a -= MOD;
   if (a < 0) a += MOD;
   return a;
}

long long expo(long long x, long long n){
    long long res = 1;

    while (n){
        if (n & 1) res = mul(res, x);
        x = mul(x, x);
        n >>= 1;
    }

    return res;
}

int gauss(int n, long long ar[MAX][MAX]){
    long long x, y;
    int i, j, k, l, p, counter = 0;

    for (i = 0; i < n; i++){
        for (p = i, j = i + 1; j < n && !ar[p][i]; j++){
            p = j;
        }
        if (!ar[p][i]) return -1;

        for (j = i; j < n; j++){
            x = ar[p][j], ar[p][j] = ar[i][j], ar[i][j] = x;
        }

        if (p != i) counter++;
        for (j = i + 1; j < n; j++){
            x = expo(ar[i][i], MOD - 2);
            x = mul(x, MOD - ar[j][i]);

            for (k = i; k < n; k++){
                ar[j][k] = ar[j][k] + mul(x, ar[i][k]);
                if (ar[j][k] >= MOD) ar[j][k] -= MOD;
            }
        }
    }
    return counter;
}

/// Finds the determinant of a square matrix
/// Returns 0 if the matrix is singular or degenerate (hence no determinant exists)
/// Absolute value of final answer should be < MOD / 2

long long determinant(int n, long long ar[MAX][MAX]){
    int i, j, free;
    long long res = 1;

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (ar[i][j] < 0) ar[i][j] += MOD;
        }
    }

    free = gauss(n, ar);
    if (free == -1) return 0; /// Determinant is 0 so matrix is not invertible, singular or degenerate matrix

    for (i = 0; i < n; i++) res = mul(res, ar[i][i]);
    if (free & 1) res = MOD - res;
    if ((MOD - res) < res) res -= MOD; /// Determinant can be negative so if determinant is more close to MOD than 0, make it negative

    return res;
}

int n;
long long ar[MAX][MAX];

int main(){
    int t, i, j, k, l;

    while (scanf("%d", &n) != EOF){
        if (n == 0) break;

        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                scanf("%lld", &ar[i][j]);
            }
        }

        printf("%lld\n", determinant(n, ar));
    }
    return 0;
}
