#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// For integer
gp_hash_table<int, int> table;

// Custom hash function approach is better
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<int, int, chash> table;

const ll TIME = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll SEED = (ll)(new ll);
const ll RANDOM = TIME ^ SEED;
const ll MOD = (int)1e9+7;
const ll MUL = (int)1e6+3;
 struct chash{
    ll operator()(ll x) const { return std::hash<ll>{}((x ^ RANDOM) % MOD * MUL); }
};
gp_hash_table<ll, int, chash> table;

unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
struct chash {
    int operator()(ll x) const { return hash_f(x); }
};
gp_hash_table<ll, int, chash> table[N][N]; 
// so table[i][j][k] is storing an integer for corresponding k as hash
unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }

// For pairs
// The better the hash function, the less collisions
// Note that hash function should not be costly
struct chash {
    int operator()(pii x) const { return x.first* 31 + x.second; }
};
gp_hash_table<pii, int, chash> table;

// Another recommended hash function by neal on CF
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
gp_hash_table<ll,int,custom_hash> safe_gp_hash_table;
unordered_map<ll,int,custom_hash> safe_umap;

typedef gp_hash_table<int, int, hash<int>, 
equal_to<int>, direct_mod_range_hashing<int>, linear_probe_fn<>,
hash_standard_resize_policy<hash_prime_size_policy, 
hash_load_check_resize_trigger<true>, true>>
gp;
gp Tree;
// Now Tree can probably be used for fenwick, indices can be long long
// S is an offset to handle negative value
// If values can be >= -1e9, S=1e9+1
// maxfen is the MAXN in fenwick, this case it was 2e9+2;
// Note that it was okay to declare gp in integer as the values were
// still in the range of int.
void add(long long p, int v) {
    for (p += S; p < maxfen; p += p & -p)
        Tree[p] += v;
}
int sum(int p) {
    int ans = 0;
    for (p += S; p; p ^= p & -p)
        ans += Tree[p];
    return ans;
}