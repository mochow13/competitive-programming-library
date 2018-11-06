#include <ext/rope>
#include <bits/stdtr1c++.h>

#define MAX 50010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;
using namespace __gnu_cxx;

rope <char> R[MAX];
int d = 0, ye = 0, vnow = 0;
char str[105], out[10000010];

int main(){
    int n, i, j, k, v, p, c, x, flag;

    while (scanf("%d", &n) != EOF){
        d = 0, vnow = 0;
        while (n--){
            scanf("%d", &flag);

            if (flag == 1){
                scanf("%d %s", &p, str);
                p -= d, vnow++;
                R[vnow] = R[vnow - 1];
                R[vnow].insert(p, str); /// Insert string str after position p
            }

            if (flag == 2){
                scanf("%d %d", &p, &c);
                p -= d, c -= d, vnow++;
                R[vnow] = R[vnow - 1];
                R[vnow].erase(p - 1, c); /// Remove c characters starting at position p
            }

            if (flag == 3){
                scanf("%d %d %d", &v, &p, &c); /// Print c characters starting at position p in version v

                v -= d, p -= d, c -= d;
                rope <char> sub = R[v].substr(p - 1, c); /// Get the substring of c characters from position p in version v
                for (auto it: sub){
                    out[ye++] = it;
                    if (it == 'c') d++;
                }
                out[ye++] = 10;
            }
        }
    }

    fwrite(out, 1, ye, stdout);
    return 0;
}
