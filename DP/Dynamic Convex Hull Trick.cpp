// source: https://github.com/niklasb/contest-algos/blob/master/convex_hull/dynamic.cpp
// Used in problem CS Squared Ends
// Problem: A is an array of n integers. The cost of subarray A[l...r] is (A[l]-A[r])^2. Partition
// the array into K subarrays having a minimum total cost
// In case of initializing 'ans', check if 1e18 is enough. Might need LLONG_MAX

const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;

        // **** May need long double typecasting here
        return (long double)(x->b - y->b)*(z->m - y->m) >= (long double)(y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};

int n, k;
ll a[10004];

int main()
{
    cin>>n>>k;
    FOR(i,1,n+1) cin>>a[i];
    vector<ll> dp(n+1,1e18);
    dp[0]=0;
    FOR(i,0,k)
    {
        HullDynamic hd;
        vector<ll> curr(n+1,1e18);

        FOR(j,1,n+1)
        {
            ll m=2*a[j];
            ll c=-a[j]*a[j]-dp[j-1];
            hd.insert_line(m,c);
            ll now=-hd.eval(a[j])+a[j]*a[j];
            curr[j]=now;
        }
        dp=curr;
    }
    prnt(dp[n]);

    return 0;
}
