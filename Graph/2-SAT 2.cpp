// for x or y add !x -> y, !y -> x
// x and y = (!x or y) and (x or !y) and (!x or !
/*
    inline void add_implication(int a, int b){
        if (a < 0) a = n - a;
        if (b < 0) b = n - b;

        adj[a].push_back(b);
        rev[b].push_back(a);
    }

    inline void add_or(int a, int b){
        add_implication(-a, b);
        add_implication(-b, a);
    }

    inline void add_xor(int a, int b){
        add_or(a, b);
        add_or(-a, -b);
    }

    inline void add_and(int a, int b){
        add_or(a, b);
        add_or(a, -b);
        add_or(-a, b);
    }

    /// force variable x to be true (if x is negative, force !x to be true)
    inline void force_true(int x){
        if (x < 0) x = n - x;
        add_implication(neg(x), x);
    }

    /// force variable x to be false (if x is negative, force !x to be false)
    inline void force_false(int x){
        if (x < 0) x = n - x;
        add_implication(x, neg(x));
    }
*/ 

struct tSAT{
    int n, id[MAX][2];
    vi G[MAX];
    int ord, dis[MAX], low[MAX], sid[MAX], scc;
    stack <int> s;
 
    tSAT(int n): n(n){
        int now=0;
        f(i,1,n+1){
            f(j,0,2){
                id[i][j]=++now;
            }
        }
    }
 
    tSAT() {}
 
    void add_edge(int u,int tu,int v,int tv){
        G[id[u][tu]].pb(id[v][tv]);
    }
 
    bool feasible(){
        scc=0; ord=0;
        mem(dis,0); mem(sid,0);
        f(i,1,2*n+1){
            if(!dis[i]) tarjan(i);
        }
        f(i,1,n+1){
            if(sid[id[i][0]]==sid[id[i][1]]) return false;
        }
        return true;
    }
 
    vi solution(){
        vi ans;
        f(i,1,n+1){
            if(sid[id[i][0]]>sid[id[i][1]]) ans.pb(i);
        }
        return ans;
    }
 
    void tarjan(int u){
        s.push(u);
        dis[u]=low[u]=++ord;
        f(i,0,G[u].size()){
            int v=G[u][i];
            if (!dis[v]){
                tarjan(v);
                low[u]=min(low[v],low[u]);
            }
            else if (!sid[v]){
                low[u]=min(dis[v],low[u]);
            }
        }
        if (low[u]==dis[u]){
            ++scc;
            while(1){
                int t=s.top();
                s.pop();
                sid[t]=scc;
                if (t==u) break;
            }
        }
    }
}
