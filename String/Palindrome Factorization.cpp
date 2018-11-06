#include <bits/stdtr1c++.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Minimum palindromic factorization for all prefixes in O(N log N)

namespace pal{
    int pl[MAX][2], gpl[MAX][2];

    inline void set(int *ar, int x, int y, int z) {
        ar[0] = x, ar[1] = y, ar[2] = z;
    }

    inline void set(int ar[][2], int i, int v) {
        if (v > 0) ar[i][v & 1] = v;
    }

    inline void copy(int *A, int *B) {
        A[0] = B[0], A[1] = B[1], A[2] = B[2];
    }

    inline void update(int ar[][2], int i, int v) {
        if (v > 0 && (ar[i][v & 1] == -1 || ar[i][v & 1] > v)) ar[i][v & 1] = v;
    }

    /// Returns a vector v such that,
    /// v[i] is the minimum k so that the prefix string str[0:i] can be partitioned into k disjoint palindromes
    inline vector <int> factorize(const char* str){
        int g[32][3], gp[32][3], gpp[32][3];
        int i, j, k, l, d, u, r, x, pg = 0, pgp = 0, pgpp = 0, n = strlen(str);

        clr(g), clr(gp), clr(gpp);
        for (int i = 0; i < n; i++) gpl[i][0] = MAX, gpl[i][1] = MAX + 1;

        for (j = 0; j < n; j++){
            for (u = 0, pgp = 0; u < pg; u++){
                i = g[u][0];
                if ((i - 1) >= 0 && str[i - 1] == str[j]){
                    g[u][0]--;
                    copy(gp[pgp++], g[u]);
                }
            }

            pgpp = 0, r = -(j + 2);
            for (u = 0; u < pgp; u++){
                i = gp[u][0], d = gp[u][1], k = gp[u][2];
                if ((i - r) != d){
                    set(gpp[pgpp++], i, i - r, 1);
                    if (k > 1) set(gpp[pgpp++], i + d, d, k - 1);
                }
                else set(gpp[pgpp++], i, d, k);
                r = i + (k - 1) * d;
            }

            if (j - 1 >= 0 && str[j - 1] == str[j]){
                set(gpp[pgpp++], j - 1, j - 1 - r, 1);
                r = j - 1;
            }
            set(gpp[pgpp++], j, j - r, 1);

            int *ptr = gpp[0];
            for (u = 1, pg = 0; u < pgpp; u++){
                int *x = gpp[u];
                if (x[1] == ptr[1]) ptr[2] += x[2];
                else {
                    copy(g[pg++], ptr);
                    ptr = x;
                }
            }
            copy(g[pg++], ptr);

            pl[j + 1][(j & 1) ^ 1] = j + 1;
            pl[j + 1][j & 1] = MAX + (j & 1);
            for (u = 0; u < pg; u++){
                i = g[u][0], d = g[u][1], k = g[u][2];
                r = i + (k - 1) * d;

                update(pl, j + 1, pl[r][0] + 1);
                update(pl, j + 1, pl[r][1] + 1);
                if (k > 1) {
                    update(pl, j + 1, gpl[i + 1 - d][0]);
                    update(pl, j + 1, gpl[i + 1 - d][1]);
                }

                if (i + 1 >= d) {
                    if (k > 1) {
                        update(gpl, i + 1 - d, pl[r][0] + 1);
                        update(gpl, i + 1 - d, pl[r][1] + 1);
                    }
                    else{
                        set(gpl, i + 1 - d, pl[r][0] + 1);
                        set(gpl, i + 1 - d, pl[r][1] + 1);
                    }
                }
            }
        }

        vector <int> res(n, 0);
        for (i = 0; i < n; i++) res[i] = min(pl[i + 1][0], pl[i + 1][1]);
        return res;
    }
}

int main(){

}
