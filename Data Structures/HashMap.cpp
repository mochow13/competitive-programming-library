#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct hashmap{
    int t, sz, hmod;
    vector <int> id;
    vector <long long> key, val;

    inline int nextPrime(int n){
        for (int i = n; ;i++){
            for (int j = 2; ;j++){
                if ((j * j) > i) return i;
                if ((i % j) == 0) break;
            }
        }
        return -1;
    }

    void clear(){t++;}

    inline int pos(unsigned long long x){
        int i = x % hmod;
        while (id[i] == t && key[i] != x) i++;
        return i;
    }

    inline void insert(long long x, long long v){
        int i = pos(x);
        if (id[i] != t) sz++;
        key[i] = x, val[i] = v, id[i] = t;
    }

    inline void erase(long long x){
        int i = pos(x);
        if (id[i] == t) key[i] = 0, val[i] = 0, id[i] = 0, sz--;
    }

    inline long long find(long long x){
        int i = pos(x);
        return (id[i] != t) ? -1 : val[i];
    }

    inline bool contains(long long x){
        int i = pos(x);
        return (id[i] == t);
    }

    inline void add(long long x, long long v){
        int i = pos(x);
        (id[i] == t) ? (val[i] += v) : (key[i] = x, val[i] = v, id[i] = t, sz++);
    }

    inline int size(){
        return sz;
    }

    hashmap(){}
    hashmap(int m){
        srand(time(0));
        m = (m << 1) - ran(1, m);
        hmod = nextPrime(max(100, m));

        sz = 0, t = 1;
        id.resize(hmod + 0x1FF, 0);
        key.resize(hmod + 0x1FF, 0), val.resize(hmod + 0x1FF, 0);
    }
};

int main(){
}
