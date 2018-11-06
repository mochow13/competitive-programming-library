const int MAXN = (1 << 21); // May not need to be changed

struct complex_base
{
    double x, y;
    complex_base(double _x = 0, double _y = 0) { x = _x; y = _y; }
    friend complex_base operator-(const complex_base &a, const complex_base &b) { return complex_base(a.x - b.x, a.y - b.y); }
    friend complex_base operator+(const complex_base &a, const complex_base &b) { return complex_base(a.x + b.x, a.y + b.y); }
    friend complex_base operator*(const complex_base &a, const complex_base &b) { return complex_base(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x); }
    friend void operator/=(complex_base &a, const double &P) { a.x /= P; a.y /= P; }
};

int bit_rev[MAXN];

void fft(complex_base *a, int lg)
{
    int n = (1 << lg);
    for (int i = 1; i < n; i++)
    {
        bit_rev[i] = (bit_rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        if (bit_rev[i] < i) swap(a[i], a[bit_rev[i]]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len;
        complex_base w(1, 0), wn(cos(ang), sin(ang));
        for (int j = 0; j < (len >> 1); j++, w = w * wn)
            for (int i = 0; i < n; i += len)
            {
                complex_base u = a[i + j], v = w * a[i + j + (len >> 1)];
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
            }
    }
}

void inv_fft(complex_base *a, int lg)
{
    int n = (1 << lg);
    for (int i = 1; i < n; i++)
    {
        bit_rev[i] = (bit_rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
        if (bit_rev[i] < i) swap(a[i], a[bit_rev[i]]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = -2 * PI / len;
        complex_base w(1, 0), wn(cos(ang), sin(ang));

        for (int j = 0; j < (len >> 1); j++, w = w * wn)
            for (int i = 0; i < n; i += len)
            {
                complex_base u = a[i + j], v = w * a[i + j + (len >> 1)];
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
            }
    }

    for (int i = 0; i < n; i++)
        a[i] /= n;
}

complex_base A[MAXN], B[MAXN];

vector<ll> mult(vector<ll> a, vector<ll> b)
{
    if (a.size() * b.size() <= 256)
    {
        vector<ll> ans(a.size() + b.size(), 0);
        for (int i = 0; i < (int)a.size(); i++)
            for (int j = 0; j < (int)b.size(); j++)
                ans[i + j] += a[i] * b[j];

        return ans;
    }

    int lg = 0; while ((1 << lg) < (a.size() + b.size())) ++lg;
    for (int i = 0; i < (1 << lg); i++) A[i] = B[i] = complex_base(0, 0);
    for (int i = 0; i < (int)a.size(); i++) A[i] = complex_base(a[i], 0);
    for (int i = 0; i < (int)b.size(); i++) B[i] = complex_base(b[i], 0);

    fft(A, lg); fft(B, lg);
    for (int i = 0; i < (1 << lg); i++)
        A[i] = A[i] * B[i];
    inv_fft(A, lg);

    vector<ll> ans(a.size() + b.size(), 0);
    for (int i = 0; i < (int)ans.size(); i++)
        ans[i] = (int)(A[i].x + 0.5);

    return ans;
}