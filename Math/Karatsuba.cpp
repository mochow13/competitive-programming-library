#define MAX 131072 /// Must be a power of 2
#define MOD 1000000007

unsigned long long temp[128];
int ptr = 0, buffer[MAX * 6];

/// n is a power of 2
void karatsuba(int n, int *a, int *b, int *res){ /// hash = 829512
    int i, j, h;
	if (n < 17){ /// Reduce recursive calls by setting a threshold
        for (i = 0; i < (n + n); i++) temp[i] = 0;
        for (i = 0; i < n; i++){
            if (a[i]){
                for (j = 0; j < n; j++){
                    temp[i + j] += ((long long)a[i] * b[j]);
                }
            }
        }
		for (i = 0; i < (n + n); i++) res[i] = temp[i] % MOD;
		return;
	}

	h = n >> 1;
	karatsuba(h, a, b, res);
	karatsuba(h, a + h, b + h, res + n);
	int *x = buffer + ptr, *y = buffer + ptr + h, *z = buffer + ptr + h + h;

	ptr += (h + h + n);
	for (i = 0; i < h; i++){
        x[i] = a[i] + a[i + h], y[i] = b[i] + b[i + h];
        if (x[i] >= MOD) x[i] -= MOD;
        if (y[i] >= MOD) y[i] -= MOD;
	}

	karatsuba(h, x, y, z);
	for (i = 0; i < n; i++) z[i] -= (res[i] + res[i + n]);
	for (i = 0; i < n; i++){
        res[i + h] = (res[i + h] + z[i]) % MOD;
        if (res[i + h] < 0) res[i + h] += MOD;
	}
	ptr -= (h + h + n);
}

/// multiplies two polynomial a(degree n) and b(degree m) and returns the result modulo MOD in a
/// returns the degree of the multiplied polynomial
/// note that a and b are changed in the process

int mul(int n, int *a, int m, int *b){ /// hash = 903808
    int i, r, c = (n < m ? n : m), d = (n > m ? n : m), *res = buffer + ptr;
    r = 1 << (32 - __builtin_clz(d) - (__builtin_popcount(d) == 1));
    for (i = d; i < r; i++) a[i] = b[i] = 0;
    for (i = c; i < d && n < m; i++) a[i] = 0;
    for (i = c; i < d && m < n; i++) b[i] = 0;

    ptr += (r << 1), karatsuba(r, a, b, res), ptr -= (r << 1);
    for (i = 0; i < (r << 1); i++) a[i] = res[i];
    return (n + m - 1);
}

int a[MAX * 2], b[MAX * 2];

int main(){
    int i, j, k, n = MAX - 10;
    for (i = 0; i < n; i++) a[i] = ran(1, 1000000000);
    for (i = 0; i < n; i++) b[i] = ran(1, 991929183);
    clock_t start = clock();
    mul(n, a, n, b);
    dbg(a[n / 2]);
    for (i = 0; i < (n << 1); i++){
        if (a[i] < 0) puts("YO");
    }
    printf("%0.5f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
