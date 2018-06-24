/*
FFT is used for fast multiplication.
Main Functionality : mult(a,b)
Parameter : vector<int>a, vector<int> b (Representing a polynomial where a[3]
contains co-efficient of the polynomial of degree 3)
Output : The polynomial a*b
*/ 

typedef complex<double> Complex;
 
void fft(vector<Complex> & a, bool inv) 
{
    int n = (int)a.size();
 
    for (int i = 1, j = 0; i<n; ++i) 
    {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) 
    {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for (int i = 0; i<n; i += len) 
        {
            Complex w(1);
            for (int j = 0; j<len / 2; ++j) 
            {
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if(inv)
    for (int i = 0; i<n; ++i)
        a[i] /= n;
 
}
 
vector<int> mult(vector<int>& a, vector<int>& b) 
{
 
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);
 
    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i<n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);
 
    vector<int> res;
    res.resize(n);
    for (size_t i = 0; i<n; ++i)
        res[i] = int(fa[i].real() + 0.5);
    return res;
}
 
 
vector<int> squ(vector<int>& a) 
{
    vector<Complex> fa(a.begin(), a.end()), fb(a.begin(), a.end());
    size_t n = 1;
    while (n < a.size())  n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);
 
    fft(fa, false); fb = fa;
    for (size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);
 
    vector<int> res;
    res.resize(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = int(fa[i].real() + 0.5);
    return res;
}