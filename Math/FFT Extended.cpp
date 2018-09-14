#include <bits/stdtr1c++.h>

#define MAXN 1048576 /// 2 * MAX at least
using namespace std;

/// Change long double to double if not required

namespace fft {
int len, last = -1, step = 0, rev[MAXN];
long long C[MAXN], D[MAXN], P[MAXN], Q[MAXN];
struct complx {
    long double real, img;
    inline complx() {
        real = img = 0.0;
    }
    inline complx conjugate() {
        return complx(real, -img);
    }
    inline complx(long double x) {
        real = x, img = 0.0;
    }
    inline complx(long double x, long double y) {
        real = x, img = y;
    }
    inline complx operator + (complx other) {
        return complx(real + other.real, img + other.img);
    }
    inline complx operator - (complx other) {
        return complx(real - other.real, img - other.img);
    }
    inline complx operator * (complx other) {
        return complx((real * other.real) - (img * other.img), (real * other.img) + (img * other.real));
    }
} u[MAXN], v[MAXN], f[MAXN], g[MAXN], dp[MAXN], inv[MAXN];

void build(int& a, long long* A, int& b, long long* B) {
    while (a > 1 && A[a - 1] == 0) a--;
    while (b > 1 && B[b - 1] == 0) b--;

    len = 1 << (32 - __builtin_clz(a + b) - (__builtin_popcount(a + b) == 1));
    for (int i = a; i < len; i++) A[i] = 0;
    for (int i = b; i < len; i++) B[i] = 0;

    if (!step++) {
        dp[1] = inv[1] = complx(1);
        for (int i = 1; (1 << i) < MAXN; i++) {
            double theta = (2.0 * acos(0.0)) / (1 << i);
            complx mul = complx(cos(theta), sin(theta));
            complx inv_mul = complx(cos(-theta), sin(-theta));

            int lim = 1 << i;
            for (int j = lim >> 1; j < lim; j++) {
                dp[2 * j] = dp[j], inv[2 * j] = inv[j];
                inv[2 * j + 1] = inv[j] * inv_mul;
                dp[2 * j + 1] = dp[j] * mul;
            }
        }
    }

    if (last != len) {
        last = len;
        int bit = (32 - __builtin_clz(len) - (__builtin_popcount(len) == 1));
        for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (bit - 1));
    }
}
/// Fast Fourier Transformation, iterative divide and conquer
void transform(complx *in, complx *out, complx* ar) {
    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
    for (int k = 1; k < len; k <<= 1) {
        for (int i = 0; i < len; i += (k << 1)) {
            for (int j = 0; j < k; j++) {
                complx z = out[i + j + k] * ar[j + k];
                out[i + j + k] = out[i + j] - z;
                out[i + j] = out[i + j] + z;
            }
        }
    }
}
/// Fast Fourier Transformation, iterative divide and conquer unrolled and optimized
void transform_unrolled(complx *in, complx *out, complx* ar) {
    for (int i = 0; i < len; i++) out[i] = in[rev[i]];
    for (int k = 1; k < len; k <<= 1) {
        for (int i = 0; i < len; i += (k << 1)) {
            complx z, *a = out + i, *b = out + i + k, *c = ar + k;
            if (k == 1) {
                z = (*b) * (*c);
                *b = *a - z, *a = *a + z;
            }

            for (int j = 0; j < k && k > 1; j += 2, a++, b++, c++) {
                z = (*b) * (*c);
                *b = *a - z, *a = *a + z;
                a++, b++, c++;
                z = (*b) * (*c);
                *b = *a - z, *a = *a + z;
            }
        }
    }
}
bool equals(int a, long long* A, int b, long long* B) {
    if (a != b) return false;
    for (a = 0; a < b && A[a] == B[a]; a++) {}
    return (a == b);
}
/// Square of a polynomial
int square(int a, long long* A) {
    build(a, A, a, A);
    for (int i = 0; i < len; i++) u[i] = complx(A[i], 0);
    transform_unrolled(u, f, dp);
    for (int i = 0; i < len; i++) u[i] = f[i] * f[i];
    transform_unrolled(u, f, inv);
    for (int i = 0; i < len; i++) A[i] = (f[i].real / (long double)len) + 0.5;
    return a + a - 1;
}
/// Multiplies two polynomials A and B and return the coefficients of their product in A
/// Function returns degree of the polynomial A * B
int multiply(int a, long long* A, int b, long long* B) {
    if (equals(a, A, b, B)) return square(a, A); /// Optimization

    build(a, A, b, B);
    for (int i = 0; i < len; i++) u[i] = complx(A[i], B[i]);
    transform_unrolled(u, f, dp);
    for (int i = 0; i < len; i++) {
        int j = (len - 1) & (len - i);
        u[i] = (f[j] * f[j] - f[i].conjugate() * f[i].conjugate()) * complx(0, -0.25 / len);
    }
    transform_unrolled(u, f, dp);
    for (int i = 0; i < len; i++) A[i] = f[i].real + 0.5;
    return a + b - 1;
}
/// Modular multiplication
int mod_multiply(int a, long long* A, int b, long long* B, int mod) {
    build(a, A, b, B);
    int flag = equals(a, A, b, B);
    for (int i = 0; i < len; i++) A[i] %= mod, B[i] %= mod;
    for (int i = 0; i < len; i++) u[i] = complx(A[i] & 32767, A[i] >> 15);
    for (int i = 0; i < len; i++) v[i] = complx(B[i] & 32767, B[i] >> 15);

    transform_unrolled(u, f, dp);
    for (int i = 0; i < len; i++) g[i] = f[i];
    if (!flag) transform_unrolled(v, g, dp);

    for (int i = 0; i < len; i++) {
        int j = (len - 1) & (len - i);
        complx c1 = f[j].conjugate(), c2 = g[j].conjugate();

        complx a1 = (f[i] + c1) * complx(0.5, 0);
        complx a2 = (f[i] - c1) * complx(0, -0.5);
        complx b1 = (g[i] + c2) * complx(0.5 / len, 0);
        complx b2 = (g[i] - c2) * complx(0, -0.5 / len);
        v[j] = a1 * b2 + a2 * b1;
        u[j] = a1 * b1 + a2 * b2 * complx(0, 1);
    }
    transform_unrolled(u, f, dp);
    transform_unrolled(v, g, dp);

    long long x, y, z;
    for (int i = 0; i < len; i++) {
        x = f[i].real + 0.5, y = g[i].real + 0.5, z = f[i].img + 0.5;
        A[i] = (x + ((y % mod) << 15) + ((z % mod) << 30)) % mod;
    }
    return a + b - 1;
}
/// Multiplies two polynomials where intermediate and final values fits in long long
int long_multiply(int a, long long* A, int b, long long* B) {
    int mod1 = 1.5e9;
    int mod2 = mod1 + 1;
    for (int i = 0; i < a; i++) C[i] = A[i];
    for (int i = 0; i < b; i++) D[i] = B[i];

    mod_multiply(a, A, b, B, mod1);
    mod_multiply(a, C, b, D, mod2);
    for (int i = 0; i < len; i++) {
        A[i] = A[i] + (C[i] - A[i] + (long long)mod2) * (long long)mod1 % mod2 * mod1;
    }
    return a + b - 1;
}
int build_convolution(int n, long long* A, long long* B) {
    int i, m, d = 0;
    for (i = 0; i < n; i++) Q[i] = Q[i + n] = B[i];
    for (i = 0; i < n; i++) P[i] = A[i], P[i + n] = 0;
    n *= 2, m = 1 << (32 - __builtin_clz(n) - (__builtin_popcount(n) == 1));
    for (i = n; i < m; i++) P[i] = Q[i] = 0;
    return n;
}
/***
    Computes the circular convolution of A and B, denoted A * B, in C
    A and B must be of equal size, if not normalize before calling function
    Example to demonstrate convolution for n = 5:

    c0 = a0b0 + a1b4 + a2b3 + a3b2 + a4b1
    c1 = a0b1 + a1b0 + a2b4 + a3b3 + a4b2
    ...
    c4 = a0b4 + a1b3 + a2b2 + a3b1 + a4b0
    Note: If linear convolution is required, pad with zeros appropriately, as in multiplication
***/
/// Returns the convolution of A and B in A
void convolution(int n, long long* A, long long* B) {
    int len = build_convolution(n, A, B);
    multiply(len, P, len, Q);
    for (int i = 0; i < n; i++) A[i] = P[i + n];
}
/// Modular convolution
void mod_convolution(int n, long long* A, long long* B, int mod) {
    int len = build_convolution(n, A, B);
    mod_multiply(len, P, len, Q, mod);
    for (int i = 0; i < n; i++) A[i] = P[i + n];
}
/// Convolution in long long
void long_convolution(int n, long long* A, long long* B) {
    int len = build_convolution(n, A, B);
    long_multiply(len, P, len, Q);
    for (int i = 0; i < n; i++) A[i] = P[i + n];
}
/// Hamming distance vector of B with every substring of length |pattern| in str
/// str and pattern consists of only '1' and '0'
/// str = "01111000010011111111110010001101000100011110101111"
/// pattern = "1001101001101110101101000"
/// Sum of values in hamming distance vector = 321
vector <int> hamming_distance(const char* str, const char* pattern) {
    int n = strlen(str), m = strlen(pattern);
    for (int i = 0; i < n; i++) P[i] = Q[i] = 0;
    for (int i = 0; i < n; i++) P[i] = str[i] == '1' ? 1 : -1;
    for (int i = 0, j = m - 1; j >= 0; i++, j--) Q[i] = pattern[j] == '1' ? 1 : -1;

    vector <int> res;
    fft::multiply(n, P, m, Q);
    for (int i = 0; (i + m) <= n; i++) {
        res.push_back(m - ((P[i + m - 1] + m) >> 1));
    }
    return res;
}
}