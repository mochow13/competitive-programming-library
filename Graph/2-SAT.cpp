const int N=20004;
int n, m, root=-1, leader[N], truths[N];
vi graph[N], rev[N], order;
bool visited[N];
// clear() if necessary
void dfs_reverse(int u)
{
    visited[u]=true;
    FOR(j,0,rev[u].size())
    {
        int v=rev[u][j];
        if(!visited[v])
            dfs_reverse(v);
    }
    order.pb(u);
}
void dfs(int u)
{
    visited[u]=true;
    leader[u]=root;

    FOR(j,0,graph[u].size())
    {
        int v=graph[u][j];

        if(!visited[v])
            dfs(v);
    }
}
void solve()
{
    for(int i=2*m; i>=1; i--)
    {
        if(!visited[i])
        {
            dfs_reverse(i);
        }
    }
    // important
    REVERSE(order);
    ms(visited,false);

    FOR(i,0,order.size())
    {
        if(!visited[order[i]])
        {
            root=order[i];
            dfs(order[i]);
        }
    }
}

bool sameSCC(int u, int v)
{
    return leader[u]==leader[v];
}
bool assign()
{
    FOR(i,0,order.size())
    {
        int u=order[i];

        if(u>m)
        {
            if(sameSCC(u,u-m)) return false;
            if(truths[leader[u]]==-1)
            {
                truths[leader[u]]=true;
                truths[leader[u-m]]=false;
            }
        }
        else
        {
            if(sameSCC(u,m+u)) return false;

            if(truths[leader[u]]==-1)
            {
                truths[leader[u]]=true;
                truths[leader[u+m]]=false;
            }
        }
    }
    return true;
}
int main()
{
    int test, cases = 1;
    scanf("%d", &test);
    while(test--)
    {
        scanf("%d%d", &n, &m);

        int u, v;
        ms(truths,-1);

        FOR(i,1,n+1)
        {
            scanf("%d%d", &u, &v);
            // For each clause (u or v), we add to edges - (~u to v), (~v to u)
            if(u > 0) 
            {
                if(v > 0)   
                {
                    graph[m+u].push_back(v); graph[m+v].push_back(u);
                    rev[v].push_back(m+u); rev[u].push_back(m+v);
                } else  {
                    graph[m+u].push_back(m-v); graph[-v].push_back(u);
                    rev[m-v].push_back(m+u); rev[u].push_back(-v);
                }
            } else {
                if(v > 0) {
                    graph[-u].push_back(v); graph[m+v].push_back(m-u);
                    rev[v].push_back(-u); rev[m-u].push_back(m+v);
                } else {
                    graph[-u].push_back(m-v); graph[-v].push_back(m-u);
                    rev[m-v].push_back(-u); rev[m-u].push_back(-v);
                }
            }
        }

        solve();
        bool okay=assign();

        if(okay)
        {
            printf("Case %d: Yes\n", cases++);

            vi allow;
            
            FOR(i,1,m+1)
            {
                if(truths[leader[i]])
                {
                    allow.pb(i);
                }
            }

            printf("%d", (int)allow.size());
            FOR(i,0,allow.size()) cout<<" "<<allow[i];
            cout<<endl;
        }
        else printf("Case %d: No\n", cases++);
    }      
    return 0;
}





