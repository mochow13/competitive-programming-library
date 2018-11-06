#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 2510
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int S[MAX][MAX], inv[MAX];

int expo(long long x, int n){
    x %= MOD;
    long long res = 1;

    while (n){
        if (n & 1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }

    return (res % MOD);
}

void Generate(){
    int i, j;
    for (i = 0; i < MAX; i++) inv[i] = expo(i, MOD - 2);

    S[0][0] = 1;
    for (i = 1; i < MAX; i++){
        S[i][0] = 0;
        for (j = 1; j <= i; j++){
            S[i][j] = ( ((long long)S[i - 1][j] * j) + S[i - 1][j - 1]) % MOD;
        }
    }
}

int faulhaber(long long n, int k){
    n %= MOD;
    if (!k) return n;

    int j;
    long long res = 0, p = 1;
    for (j = 0; j <= k; j++){
        p = (p * (n + 1 - j)) % MOD;
        res = (res + (((S[k][j] * p) % MOD) * inv[j + 1])) % MOD;
    }

    return (res % MOD);
}

int main(){
    Generate();
    printf("%d\n", faulhaber(1001212, 1000));
    return 0;
}
