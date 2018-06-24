// Min Cost Arboroscense class in C++
// Directed MST
// dir_mst returns the cost O(EV)?

struct Edge {  
    int u, v;  
    ll dist;
    int kbps;
};
  
struct MinCostArborescence{  
    int n, m;  
    Edge allEdges[MAX];  
    int done[62], prev[62], id[62];
    ll in[62];  
  
    void init(int n) 
    {  
        this->n = n;  
        m = 0;  
    }  
  
    void add_Edge(int u, int v, ll dist) 
    {  
        allEdges[m++] = {u,v,dist,0};  
    }  
  
    void add_Edge(Edge e) 
    {  
        allEdges[m++] = e;  
    }  
  
    ll dir_mst(int root) {  
        ll ans = 0;  
        while (true) {  
            for (int i = 0; i < n; i++) in[i] = INF;  
            for (int i = 0; i < m; i++) { 
                int u = allEdges[i].u;  
                int v = allEdges[i].v;  
                if (allEdges[i].dist < in[v] && u != v) {  
                    in[v] = allEdges[i].dist;  
                    prev[v] = u;  
                }  
            }  
  
            for (int i = 0; i < n; i++) { 
                if (i == root) continue;  
                if (in[i] == INF) return -1;  
            }  
  
            int cnt = 0;  
            memset(id, -1, sizeof(id));  
            memset(done, -1, sizeof(done));  
            in[root] = 0;  
  
            for (int i = 0; i < n; i++) 
            {
                ans += in[i];  
                int v = i;  
                while (done[v] != i && id[v] == -1 && v != root) {  
                    done[v] = i;  
                    v = prev[v];  
                }  
                if (v != root && id[v] == -1) {  
                    for (int u = prev[v]; u != v; u = prev[u])  
                        id[u] = cnt;  
                    id[v] = cnt++;
                }  
            }  
            if (cnt == 0) break;  
            for (int i = 0; i < n; i++)  
                if (id[i] == -1) id[i] = cnt++;  
            for (int i = 0; i < m; i++) {  
                int v = allEdges[i].v;  
                allEdges[i].u = id[allEdges[i].u];  
                allEdges[i].v = id[allEdges[i].v];  
                if (allEdges[i].u != allEdges[i].v)  
                    allEdges[i].dist -= in[v];  
            }  
            n = cnt;  
            root = id[root];  
        }  
        return ans;  
    }  
} Arboroscense;