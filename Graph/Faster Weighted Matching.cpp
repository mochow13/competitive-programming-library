#include <bits/stdtr1c++.h>

#define MAX 1002
#define MAXIMIZE +1
#define MINIMIZE -1

using ll = long long;

#define inf (~0U >> 1)
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;
/* call: wm::hungarian(number_of_nodes_on_left,on_right,matrix_of_weights,flag)
   match[i] contains matched right node with i-th left node
*/
namespace wm{ /// hash = 581023
    bool visited[MAX];
    ll U[MAX], V[MAX], P[MAX], way[MAX], minv[MAX], match[MAX], ar[MAX][MAX];

    /// n = number of row and m = number of columns in 1 based, flag = MAXIMIZE or MINIMIZE
    /// match[i] contains the column to which row i is matched
    ll hungarian(ll n, ll m, ll mat[MAX][MAX], ll flag){
        clr(U), clr(V), clr(P), clr(ar), clr(way);

        for (ll i = 1; i <= n; i++){
            for (ll j = 1; j <= m; j++){
                ar[i][j] = mat[i][j];
                if (flag == MAXIMIZE) ar[i][j] = -ar[i][j];
            }
        }
        if (n > m) m = n;

        ll i, j, a, b, c, d, r, w;
        for (i = 1; i <= n; i++){
            P[0] = i, b = 0;
            for (j = 0; j <= m; j++) minv[j] = inf, visited[j] = false;

            do{
                visited[b] = true;
                a = P[b], d = 0, w = inf;

                for (j = 1; j <= m; j++){
                    if (!visited[j]){
                        r = ar[a][j] - U[a] - V[j];
                        if (r < minv[j]) minv[j] = r, way[j] = b;
                        if (minv[j] < w) w = minv[j], d = j;
                    }
                }

                for (j = 0; j <= m; j++){
                    if (visited[j]) U[P[j]] += w, V[j] -= w;
                    else minv[j] -= w;
                }
                b = d;
            } while (P[b] != 0);

            do{
                d = way[b];
                P[b] = P[d], b = d;
            } while (b != 0);
        }
        for (j = 1; j <= m; j++) match[P[j]] = j;

        return (flag == MINIMIZE) ? -V[0] : V[0];
    }
}
