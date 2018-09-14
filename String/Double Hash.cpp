struct Hash {
    ll h1[MAX], h2[MAX], pwr1[MAX], pwr2[MAX];
    ll p1, p2, mod1, mod2, n;
    Hash(char *s, ll n, ll p1, ll p2, ll mod1, ll mod2): n(n), p1(p1), p2(p2), mod1(mod1), mod2(mod2) {
        ll th1 = 0, th2 = 0, pw1 = 1, pw2 = 1;
        FOR(i,0,n) {
            pwr1[i] = pw1;
            pwr2[i] = pw2;
            th1 = (th1 + s[i] * pwr1[i]) % mod1;
            th2 = (th2 + s[i] * pwr2[i]) % mod2;
            h1[i] = th1;
            h2[i] = th2;
            pw1 = (pw1 * p1) % mod1;
            pw2 = (pw2 * p2) % mod2;
        }
        pwr1[n] = pw1;
        pwr2[n] = pw2;
    }
    Hash() {}
    pair<ll,ll> getHash(ll i, ll j) {
        ll ret1, ret2;
        if (!i) {
            ret1 = (h1[j] * pwr1[n - i]) % mod1;
            ret2 = (h2[j] * pwr2[n - i]) % mod2;
        }
        else {
            ret1 = ((h1[j] - h1[i - 1]) * pwr1[n - i]) % mod1;
            ret1 = (ret1 + mod1) % mod1;
            ret2 = ((h2[j] - h2[i - 1]) * pwr2[n - i]) % mod2;
            ret2 = (ret2 + mod2) % mod2;
        }
        return MP(ret1, ret2);
    }

    bool areEqual(ll l, ll r, ll i, ll j) {
        return getHash(l, r) == getHash(i, j);
    }
} H;