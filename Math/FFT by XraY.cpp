typedef long double ld;
#define mp make_pair
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define sz(x) ((int)(x).size())

const ld pi = acos((ld) - 1);
//BEGIN ALGO
namespace FFT {
struct com {
	ld x, y;

	com(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}

	inline com operator + (const com &c) const {
		return com(x + c.x, y + c.y);
	}
	inline com operator - (const com &c) const {
		return com(x - c.x, y - c.y);
	}
	inline com operator * (const com &c) const {
		return com(x * c.x - y * c.y, x * c.y + y * c.x);
	}
	inline com conj() const {
		return com(x, -y);
	}
};

const static int maxk = 21, maxn = (1 << maxk) + 1;
com ws[maxn];
int dp[maxn];
com rs[maxn];
int n, k;
int lastk = -1;

void fft(com *a, bool torev = 0) {
	if (lastk != k) {
		lastk = k;
		dp[0] = 0;

		for (int i = 1, g = -1; i < n; ++i) {
			if (!(i & (i - 1))) {
				++g;
			}
			dp[i] = dp[i ^ (1 << g)] ^ (1 << (k - 1 - g));
		}

		ws[1] = com(1, 0);
		for (int two = 0; two < k - 1; ++two) {
			ld alf = pi / n * (1 << (k - 1 - two));
			com cur = com(cos(alf), sin(alf));

			int p2 = (1 << two), p3 = p2 * 2;
			for (int j = p2; j < p3; ++j) {
				ws[j * 2 + 1] = (ws[j * 2] = ws[j]) * cur;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (i < dp[i]) {
			swap(a[i], a[dp[i]]);
		}
	}
	if (torev) {
		for (int i = 0; i < n; ++i) {
			a[i].y = -a[i].y;
		}
	}
	for (int len = 1; len < n; len <<= 1) {
		for (int i = 0; i < n; i += len) {
			int wit = len;
			for (int it = 0, j = i + len; it < len; ++it, ++i, ++j) {
				com tmp = a[j] * ws[wit++];
				a[j] = a[i] - tmp;
				a[i] = a[i] + tmp;
			}
		}
	}
}

com a[maxn];
int mult(int na, int *_a, int nb, int *_b, long long *ans) {
	if (!na || !nb) {
		return 0;
	}
	for (k = 0, n = 1; n < na + nb - 1; n <<= 1, ++k) ;
	assert(n < maxn);
	for (int i = 0; i < n; ++i) {
		a[i] = com(i < na ? _a[i] : 0, i < nb ? _b[i] : 0);
	}
	fft(a);
	a[n] = a[0];
	for (int i = 0; i <= n - i; ++i) {
		a[i] = (a[i] * a[i] - (a[n - i] * a[n - i]).conj()) * com(0, (ld) - 1 / n / 4);
		a[n - i] = a[i].conj();
	}
	fft(a, 1);
	int res = 0;
	for (int i = 0; i < n; ++i) {
		long long val = (long long) round(a[i].x);
		assert(abs(val - a[i].x) < 1e-1);
		if (val) {
			assert(i < na + nb - 1);
			while (res < i) {
				ans[res++] = 0;
			}
			ans[res++] = val;
		}
	}
	return res;
}
};

int main()
{
	// ios_base::sync_with_stdio(0);
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	int test, cases = 1;



	return 0;
}





