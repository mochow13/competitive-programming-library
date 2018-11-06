// Tested:
// - FBHC 2016 R3 - Problem E
// - https://open.kattis.com/problems/polymul2 (need long double)
// Note:
// - a[2] will have size <= 2*n
// - When rounding, careful with negative numbers:
int my_round(double x) {
	if (x < 0) return -my_round(-x);
	return (int) (x + 1e-3);
}
const int N = 1 << 18;
typedef complex<long double> cplex; // may need long double
int rev[N];
cplex wlen_pw[N], fa[N], fb[N];

void fft(cplex a[], int n, bool invert) {
	for (int i = 0; i < n; ++i) if (i < rev[i]) swap (a[i], a[rev[i]]);

	for (int len = 2; len <= n; len <<= 1) {
		double alpha = 2 * PI / len * (invert ? -1 : +1);
		int len2 = len >> 1;

		wlen_pw[0] = cplex(1, 0);
		cplex wlen(cos(alpha), sin(alpha));
		for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i - 1] * wlen;

		for (int i = 0; i < n; i += len) {
			cplex t, *pu = a + i, *pv = a + i + len2,
			          *pu_end = a + i + len2, *pw = wlen_pw;
			for (; pu != pu_end; ++pu, ++pv, ++pw) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}

	if (invert) FOR(i, 0, n) a[i] /= n;
}
void calcRev(int n, int logn) {
	FOR(i, 0, n) {
		rev[i] = 0;
		FOR(j, 0, logn) if (i & (1 << j)) rev[i] |= 1 << (logn - 1 - j);
	}
}
void mulpoly(int a[], int b[], ll c[], int na, int nb, int &n) {
	int l = max(na, nb), logn = 0;
	for (n = 1; n < l; n <<= 1) ++logn;
	n <<= 1; ++logn;
	calcRev(n, logn);

	FOR(i, 0, n) fa[i] = fb[i] = cplex(0);
	FOR(i, 0, na) fa[i] = cplex(a[i]);
	FOR(i, 0, nb) fb[i] = cplex(b[i]);

	fft(fa, n, false);
	fft(fb, n, false);

	FOR(i, 0, n) fa[i] *= fb[i];
	fft(fa, n, true);
	// if everything is double/long double, we don't add 0.5
	FOR(i, 0, n) c[i] = (ll)(fa[i].real() + 0.5);
}
// call mulpoly(first_poly,second_poly,output,size_first,size_second,size_output)
