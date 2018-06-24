vector< int > graph[MAX];
int n, m, match[MAX], dist[MAX];
int NIL=0;

bool bfs() 
{
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) 
    {
        if(match[i]==NIL) 
        {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) 
    {
        u = Q.front(); Q.pop();
        if(u!=NIL) 
        {
            len = graph[u].size();
            for(i=0; i<len; i++) 
            {
                v = graph[u][i];
                if(dist[match[v]]==INF) 
                {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u) 
{
    int i, v, len;
    if(u!=NIL) 
    {
        len = graph[u].size();
        for(i=0; i<len; i++) 
        {
            v = graph[u][i];
            if(dist[match[v]]==dist[u]+1) 
            {
                if(dfs(match[v])) 
                {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() 
{
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in graph
    // All nodes on left and right should be distinct
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
}

void clear()
{
    FOR(j,0,MAX) graph[j].clear();
    ms(match,NIL);
}

int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

    // SPOJ - Fast Maximum Matching

	int p, x, y;

	scanf("%d%d%d", &n, &m, &p);

	FOR(i,0,p)
	{
		scanf("%d%d", &x, &y);
		graph[x].pb(n+y);
		graph[n+y].pb(x);
	}

	printf("%d\n", hopcroft_karp());

	return 0;
}







