LL mod;
LL S[105][105];
// Find 1^k+2^k+...+n^k % mod
void solve() {
	LL n, k;
	scanf("%lld %lld %lld", &n, &k, &mod);
	/*
	x^k = sum (i=1 to k) Stirling2(k, i) * i! * ncr(x, i)
	sum (x = 0 to n) x^k
		= sum (i = 0 to k) Stirling2(k, i) * i! * sum (x = 0 to n) ncr(x, i)
		= sum (i = 0 to k) Stirling2(k, i) * i! * ncr(n + 1, i + 1)
		= sum (i = 0 to k) Stirling2(k, i) * i! * (n + 1)! / (i + 1)! / (n - i)!
		= sum (i = 0 to k) Stirling2(k, i) * (n - i + 1) * (n - i + 2) * ... (n + 1) / (i + 1)
	*/
	S[0][0] = 1 % mod;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= i; j++) {
			if (i == j) S[i][j] = 1 % mod;
			else S[i][j] = (j * S[i - 1][j] + S[i - 1][j - 1]) % mod;
		}
	}

	LL ans = 0;
	for (int i = 0; i <= k; i++) {
		LL fact = 1, z = i + 1;
		for (LL j = n - i + 1; j <= n + 1; j++) {
			LL mul = j;
			if (mul % z == 0) {
				mul /= z;
				z /= z;
			}
			fact = (fact * mul) % mod;
		}
		ans = (ans + S[k][i] * fact) % mod;
	}
	printf("%lld\n", ans);
}
