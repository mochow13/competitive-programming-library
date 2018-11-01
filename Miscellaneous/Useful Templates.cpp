template <class T> inline T bigmod(T p, T e, T M)
{
    ll ret = 1;
    for (; e > 0; e >>= 1)
    {
        if (e & 1) ret = (ret * p) % M;
        p = (p * p) % M;
    } return (T)ret;
}

template <class T> inline T gcd(T a, T b) {if (b == 0)return a; return gcd(b, a % b);}
template <class T> inline T modinverse(T a, T M) {return bigmod(a, M - 2, M);}
template <class T> inline T lcm(T a, T b) {a = abs(a); b = abs(b); return (a / gcd(a, b)) * b;}
template <class T, class X> inline bool getbit(T a, X i) { T t = 1; return ((a & (t << i)) > 0);}
template <class T, class X> inline T setbit(T a, X i) { T t = 1; return (a | (t << i)); }
template <class T, class X> inline T resetbit(T a, X i) { T t = 1; return (a & (~(t << i)));}

inline ll getnum()
{
    char c = getchar();
    ll num, sign = 1;
    for (; c < '0' || c > '9'; c = getchar())if (c == '-')sign = -1;
    for (num = 0; c >= '0' && c <= '9';)
    {
        c -= '0';
        num = num * 10 + c;
        c = getchar();
    }
    return num * sign;
}

inline ll power(ll a, ll b)
{
    ll multiply = 1;
    FOR(i, 0, b)
    {
        multiply *= a;
    }
    return multiply;
}