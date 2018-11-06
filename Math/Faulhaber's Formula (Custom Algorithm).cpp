#include <bits/stdtr1c++.h>

#define MAX 1010
#define MOD 1000000007
using namespace std;
namespace fool{
    #define MAXN 10000

    tr1::unordered_map <unsigned long long, int> mp;
    int inv, P[MAX], binomial[MAX][MAX], dp[MAXN][MAX];

    long long expo(long long x, long long n){
        x %= MOD;
        long long res = 1;

        while (n){
            if (n & 1) res = (res * x) % MOD;
            x = (x * x) % MOD;
            n >>= 1;
        }

        return (res % MOD);
    }

    void init(){
        int i, j;
        mp.clear();
        inv = expo(2, MOD - 2);

        P[0] = 1;
        for (i = 1; i < MAX; i++){
            P[i] = (P[i - 1] << 1);
            if (P[i] >= MOD) P[i] -= MOD;
        }

        for (i = 0; i < MAX; i++){
            for (j = 0; j <= i; j++){
                if (i == j || !j) binomial[i][j] = 1;
                else{
                    binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]);
                    if (binomial[i][j] >= MOD) binomial[i][j] -= MOD;
                }
            }
        }

        for (i = 1; i < MAXN; i++){
            long long x = 1;
            for (j = 0; j < MAX; j++){
                dp[i][j] = dp[i - 1][j] + x;
                if (dp[i][j] >= MOD) dp[i][j] -= MOD;
                x = (x * i) % MOD;
            }
        }
    }

    /// Returns (1^k + 2^k + 3^k + .... n^k) % MOD
    long long F(unsigned long long n, int k){
        if (n < MAXN) return dp[n][k];

        if (n == 1) return 1;
        if (n == 2) return (P[k] + 1) % MOD;
        if (!k) return (n % MOD);
        if (k == 1){
            n %= MOD;
            return (((n * (n + 1)) % MOD) * inv) % MOD;
        }

        unsigned long long h = (n << 10LL) | k; /// Change hash function according to limits of n and k
        long long res = mp[h];
        if (res) return res;

        if (n & 1) res = F(n - 1, k) + expo(n, k);
        else{
            long long m, z;
            m = n >> 1;
            res = (F(m, k) * P[k]) % MOD;

            m--, res++;
            for (int i = 0; i <= k; i++){
                z = (F(m, i) * binomial[k][i]) % MOD;
                z = (z * P[i]) % MOD;
                res += z;
            }
        }

        res %= MOD;
        return (mp[h] = res);
    }

    long long faulhaber(unsigned long long n, int k){
        ///fool::init();
        return F(n, k);
    }
}

int main(){
    fool::init();
    int t, i, j;
    long long n, k, res;

    cin >> t;
    while (t--){
        cin >> n >> k;
        res = fool::faulhaber(n, k);
        cout << res << endl;
    }
    return 0;
}
