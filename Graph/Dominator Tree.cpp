// Problem: LightOJ Sabotaging Contest
// n - number of cities, m - number of edges, (u,v,t) - edge and cost
// Each of the q lines gives a query of k cities n[1],n[2],...,n[k];
// We have to find the number of nodes where if any one of them is removed, the 
// shortest path to 0 from n[1]...n[k] will be increased. We also have to print 
// the number of nodes which will be affected by such removal.

/* Solution
	Run Dijkstra, build shortest path dag, take topsort order and reverse it,
	according to the reversed order add one edge at a time to build dominator tree
	Finally, run dfs to find the level of each node and subtree size. Answer is the
	(level of the lca of the nodes n[1]...n[k] + 1) and subtree size of this ancestor
*/

vi graph[MAX], cost[MAX], dag[MAX], parent[MAX], Tree[MAX];
int u, v, t, n, m;
int dist[MAX];
vector<int> all;
int L[MAX], table[MAX][18], sub[MAX];
bool visited[MAX];

void clear()
{
	FOR(i,0,n) 
	{
		graph[i].clear(); 
		cost[i].clear(); 
		dag[i].clear();
		parent[i].clear();
		Tree[i].clear();
		sub[i]=0;
	}
	all.clear();
	ms(table,-1);
	ms(visited,false);
}

void dfs(int u)
{
	sub[u]++;

	FOR(j,0,Tree[u].size())
	{
		int v=Tree[u][j];
		dfs(v);
		sub[u]+=sub[v];
	}
}

int query(int p, int q)
{
	if(L[p]<L[q]) swap(p,q);
	
	int x=1;
	
	while(true)
	{
		if((1<<(x+1))>L[p])
			break;
		x++;
	}
	
	FORr(i,x,0)
	{
		if(L[p]-(1<<i) >= L[q])
			p=table[p][i];
	}
	
	if(p==q) return p;
	
	FORr(i,x,0)
	{
		if(table[p][i]!=-1 && table[p][i]!=table[q][i])
		{
			p=table[p][i];
			q=table[q][i];
		}
	}
	
	return table[p][0];
}

void build(int curr)
{		
	for(int j=1; (1<<j) < n; j++)
	{
		if(table[curr][j-1]!=-1)
			table[curr][j]=table[table[curr][j-1]][j-1];
	}
}

void dijkstra()
{
	priority_queue<pii,vpii,greater<pii> > PQ;
	PQ.push(pii(0,0));
	FOR(i,0,n) dist[i]=INF;
	dist[0]=0;

	while(!PQ.empty())
	{
		pii t=PQ.top();
		PQ.pop();

		int u=t.second;

		FOR(j,0,graph[u].size())
		{
			int v=graph[u][j];

			if(dist[u]+cost[u][j]<dist[v])
			{
				dist[v]=dist[u]+cost[u][j];
				PQ.push(pii(dist[v],v));
			}
		}
	}
}

void buildDag()
{
	FOR(i,0,n)
	{
		FOR(j,0,graph[i].size())
		{
			int v=graph[i][j];

			if(dist[i]!=INF && dist[v]!=INF && dist[v]==dist[i]+cost[i][j])
			{
				dag[i].pb(v);
				parent[v].pb(i);
			}
		}
	}
}

void topsort(int u)
{
	visited[u]=true;

	FOR(j,0,dag[u].size())
	{
		if(!visited[dag[u][j]]) topsort(dag[u][j]);
	}

	all.pb(u);
}

void buildTree()
{
	L[0]=0;
	REVERSE(all);

	FOR(i,0,all.size())
	{
		int now=all[i];

		if(parent[now].size())
		{
			int anc=parent[now][0];

			FOR(j,1,parent[now].size())
			{
				anc=query(anc,parent[now][j]);
			}

			L[now]=L[anc]+1;
			table[now][0]=anc;
			Tree[anc].pb(now);

			build(now);
		}
	}
}

int main()
{
    int test, cases=1;

    scanf("%d", &test);

    while(test--)
    {
    	scanf("%d%d", &n, &m);

    	FOR(i,0,m)
    	{
    		scanf("%d%d%d", &u, &v, &t);

    		graph[u].pb(v);
    		graph[v].pb(u);
    		cost[u].pb(t);
    		cost[v].pb(t);
    	}

    	dijkstra();
    	buildDag();
    	topsort(0);
    	buildTree();
    	dfs(0);

    	int q; scanf("%d", &q);

    	printf("Case %d:\n", cases++);

    	while(q--)
    	{
    		int x, u;

    		scanf("%d", &x);

    		int anc=-1;

    		FOR(i,0,x)
    		{
    			scanf("%d", &u);

    			if(dist[u]==INF) continue;

    			if(anc==-1) anc=u;
    			else anc=query(anc,u);
    		}

    		if(anc==-1) printf("0\n");
    		else printf("%d %d\n", L[anc]+1, sub[anc]);
    	}

    	clear();
    }
    return 0;
}

