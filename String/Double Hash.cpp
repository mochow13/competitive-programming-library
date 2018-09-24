const int p1 = 7919;
const int mod1 = 1000004249;
const int p2 = 2203;
const int mod2 = 1000000289;

ll pwr1[MAX+7], pwr2[MAX+7];

void precalc()
{
    ll pw1 = 1, pw2 = 1;

    FOR(i,0,MAX)
    {
        pwr1[i] = pw1;
        pwr2[i] = pw2;

        pw1 = (pw1 * p1) % mod1;
        pw2 = (pw2 * p2) % mod2;        
    }

    pwr1[MAX] = pw1;
    pwr2[MAX] = pw2;
}

struct Hash {
    ll h1[MAX], h2[MAX];
    int n; // length of s

    Hash(char *s, int n): n(n) {
        ll th1 = 0, th2 = 0;
        FOR(i, 0, n) {
            th1 = (th1 + s[i] * pwr1[i]) % mod1;
            th2 = (th2 + s[i] * pwr2[i]) % mod2;
            h1[i] = th1;
            h2[i] = th2;
        }
    }
    Hash() {}
    pair<ll, ll> getHash(ll i, ll j) {

        if(i>j) return {0,0};

        ll ret1, ret2;
        if (!i) {
            ret1 = h1[j];
            ret2 = h2[j];
        }
        else {
            ret1 = (h1[j] - h1[i - 1]) % mod1;
            if (ret1 < 0) ret1 += mod1;
            ret2 = (h2[j] - h2[i - 1]) % mod2;
            if (ret2 < 0) ret2 += mod2;
        }
        return MP(ret1, ret2);
    }
};