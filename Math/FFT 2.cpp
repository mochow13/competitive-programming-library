/* To multiply two polynomials a and b, do the following:
sz = power of 2 > n+m, where n = size(a), m = size(b)
a.assign(sz,CD(0,0)); b.assign(sz,CD(0,0));
Assign coefficients to the polynomials. If i-th coefff is 1, assign CD(1,0). 
Then call fast.fft(a), fast.fft(b);
vi result = fast.multiply(a,b)
*/
struct Complex
{
    double x, y;    //x + i y
    Complex(double a = 0, double b = 0) : x(a), y(b) {}
    Complex operator+(Complex r)    {return Complex(x + r.x, y + r.y);}
    Complex operator-(Complex r)    {return Complex(x - r.x, y - r.y);}
    Complex operator*(Complex r)    {return Complex(x * r.x - y * r.y, x * r.y + y * r.x);}
    Complex operator/(double d)     {return Complex(x / d, y / d);}
};

typedef Complex CD;

struct FFT
{
    int N;
    vector<int> perm;
    vector<CD> wn;

    void precalculate() {
        perm.resize(N);
        perm[0] = 0;

        for (int k = 1; k < N; k <<= 1) {
            for (int i = 0; i < k; i++) {
                perm[i] <<= 1;
                perm[i + k] = 1 + perm[i];
            }
        }

        wn.resize(N + 1);
        CD w (cos(2 * PI / N), sin(2 * PI / N));
        wn[0] = CD(1);
        for (int i = 1; i <= N; i++)
            wn[i] = wn[i - 1] * w;
    }

    void fft(vector<CD> &v, bool invert = false) {
        if (v.size() != perm.size()) {
            N = v.size();
            assert(N && (N & (N - 1)) == 0);
            precalculate();
        }

        for (int i = 0; i < N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int len = 2; len <= N; len <<= 1)
            for (int i = 0; i < N; i += len)
                for (int j = 0; j < len / 2; j++) {
                    int id = j * (N / len);
                    if (invert) id = N - id;
                    CD w = wn[id];

                    CD x = v[i + j], y = w * v[i + j + len / 2];
                    v[i + j] = x + y;
                    v[i + j + len / 2] = x - y;
                }

        if (invert)
            for (CD &x : v) x = x / N;
    }

    vector<int> multiply(vector<CD> fa, vector<CD> fb) {
        int n = fa.size();
        for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
        fft(fa, true);
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = round(fa[i].x);
        return ans;
    }
} fast;