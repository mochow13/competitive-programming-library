#include <bits/stdtr1c++.h>

#define MAX 505
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;
/// Minimum path cover/Maximum independent set in DAG
namespace dag{
     /// For transitive closure and minimum path cover with not necessarily disjoint vertex
    bool ar[MAX][MAX];

    vector <int> adj[MAX];
    bool visited[MAX], first_set[MAX], second_set[MAX];
    int n, L[MAX], R[MAX], D[MAX], Q[MAX], dis[MAX], parent[MAX];

    inline void init(int nodes){ /// Number of vertices in DAG
        n = nodes;
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    inline void add_edge(int u, int v){ /// 0 based index, directed edge of DAG
        adj[u].push_back(v);
    }

    bool dfs(int i){
        int len = adj[i].size();
        for (int j = 0; j < len; j++){
            int x = adj[i][j];
            if (L[x] == -1 || (parent[L[x]] == i)){
                if (L[x] == -1 || dfs(L[x])){
                    L[x] = i, R[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    bool bfs(){
        clr(visited);
        int i, j, x, d, f = 0, l = 0;

        for (i = 0; i < n; i++){
            if (R[i] == -1){
                visited[i] = true;
                Q[l++] = i, dis[i] = 0;
            }
        }

        while (f < l){
            i = Q[f++];
            int len = adj[i].size();
            for (j = 0; j < len; j++){
                x = adj[i][j], d = L[x];
                if (d == -1) return true;

                else if (!visited[d]){
                    Q[l++] = d;
                    parent[d] = i, visited[d] = true, dis[d] = dis[i] + 1;
                }
            }
        }
        return false;
    }

    void get_path(int i){
        first_set[i] = true;
        int j, x, len = adj[i].size();

        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (!second_set[x] && L[x] != -1){
                second_set[x] = true;
                get_path(L[x]);
            }
        }
    }

    void transitive_closure(){ /// Transitive closure in O(n * m)
        clr(ar);
        int i, j, k, l;
        for (i = 0; i < n; i++){
            l = adj[i].size();
            for (j = 0; j < l; j++){
                ar[i][adj[i][j]] = true;
            }
            adj[i].clear();
        }

        for (k = 0; k < n; k++){
            for (i = 0; i < n; i++){
                if (ar[i][k]){
                    for (j = 0; j < n; j++){
                        if (ar[k][j]) ar[i][j] = true;
                    }
                }
            }
        }

        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                if (i != j && ar[i][j]){
                    adj[i].push_back(j);
                }
            }
        }
    }
    /// Minimum vertex disjoint path cover in DAG. Handle isolated vertices appropriately
    int minimum_disjoint_path_cover() {
        int i, res = 0;
        memset(L, -1, sizeof(L));
        memset(R, -1, sizeof(R));

        while (bfs()){
            for (i = 0; i < n; i++){
                if (R[i] == -1 && dfs(i)) res++;
            }
        }

        return n - res;
    }

    int minimum_path_cover(){ /// Minimum path cover in DAG. Handle isolated vertices appropriately
        transitive_closure();
        return minimum_disjoint_path_cover();
    }
    /// Minimum vertex cover of DAG, equal to maximum bipartite matching
    vector <int> minimum_vertex_cover(){ 
        int i, res = 0;
        memset(L, -1, sizeof(L));
        memset(R, -1, sizeof(R));

        while (bfs()){
            for (i = 0; i < n; i++){
                if (R[i] == -1 && dfs(i)) res++;
            }
        }

        vector <int> v;
        clr(first_set), clr(second_set);
        for (i = 0; i < n; i++){
            if (R[i] == -1) get_path(i);
        }

        for (i = 0; i < n; i++){
            if (!first_set[i] || second_set[i]) v.push_back(i);
        }

        return v;
    }
    /// Maximum independent set of DAG, all vertices not in minimum vertex cover
    vector <int> maximum_independent_set() {
        vector <int> v = minimum_vertex_cover();
        clr(visited);
        int i, len = v.size();
        for (i = 0; i < len; i++) visited[v[i]] = true;

        vector <int> res;
        for (i = 0; i < n; i++){
            if (!visited[i]) res.push_back(i);
        }
        return res;
    }
}