int fact[MAX], inv[MAX];
int expo(int a, int b){
    int res = 1;

    while (b){
        if (b & 1) res = (long long)res * a % MOD;
        a = (long long)a * a % MOD;
        b >>= 1;
    }
    return res;
}
void Generate(){
    int i, x;
    for (fact[0] = 1, i = 1; i < MAX; i++) fact[i] = ((long long)i * fact[i - 1]) % MOD;

    /// inv[i] = Inverse modulo of fact[i]
    inv[MAX - 1] = expo(fact[MAX - 1], MOD - 2);
    for (i = MAX - 2; i >= 0; i--) inv[i] = ((long long)inv[i + 1] * (i + 1)) % MOD;

    /// Inverse modulo of numbers 1 to MAX in linear time below
    inv[1] = 1;
	for (i = 2; i < MAX; i++){
        inv[i] = MOD - ((MOD / i) * (long long)inv[MOD % i]) % MOD;
        if (inv[i] < 0) inv[i] += MOD;
	}
}

int main(){
    Generate();
    printf("%d\n", inv[35]);
    printf("%d\n", expo(fact[35], MOD - 2));
    return 0;
}
