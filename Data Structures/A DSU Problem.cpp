/* Problem: You are given a graph with edge-weights. Each node has some color. 
Now you are also given some queries of the form (starting_node, weight). The 
query means you can start from the starting_node and you can visit only those
edges which have wight <= weight. You need to print the color which will occur
the maximum time in your journey. If two color occurs the same, output the lower
indexed one.
Solution: idea is to use DSU small to large merging with binary-lifting.
*/
const int LOG = 17;
int n, m, a[MAX], parent[MAX], up[MAX][LOG], weight[MAX][LOG];
// best (count,color_number) pair on a component after adding an edge
pii best[MAX]; 
// (weight,color) pair which means you can get max-occurrence of 'color' with 'weight'
vpii ans[MAX]; 
// (color,cnt) pair for each component, stores all of them
set<pii> color[MAX];
vector<array<int,3>> edges;

void clear()
{
	// Initialize weights and 2^j parent of each node.
	// Initially, each node is 2^j-th parent of itself
	FOR(i,1,n+1)
	{
		FOR(j,0,LOG)
			weight[i][j] = 1e9, up[i][j]=i;
	}
	edges.clear();
	FOR(i,1,n+1) color[i].clear(), ans[i].clear();
}

int findParent(int r)
{
	if(parent[r]==r) return r;
	return parent[r]=findParent(parent[r]);
}

void merge(int u, int v)
{
	// merge u into v
	for(auto it: color[u])
	{
		auto curr = color[v].lower_bound({it.first,-1});
		int cnt = it.second;

		if(curr!=end(color[v]) && curr->first==it.first)
		{
			cnt+=curr->second;
			color[v].erase(curr);
		}

		color[v].insert({it.first,cnt});
		// best (cnt,color) pair for component v, -it.first for ensuring
		// that we get the smallest index while max-ing
		best[v] = max(best[v],{cnt,-it.first});
	}
}

void solve()
{
	FOR(i,1,n+1) parent[i] = i;
	for(auto it: edges)
	{
		auto [w,u,v] = it;

		u = findParent(u);
		v = findParent(v);

		if(color[u].size()>color[v].size())
			swap(u,v);
		if(u!=v)
		{
			merge(u,v);
			parent[u] = v;
			// after merging (u,v), we store best answer
			// for the component v in ans[v]
			ans[v].pb({w,-best[v].second});
			up[u][0] = v;
			weight[u][0] = w;
		}
		// note that if u==v, that edge and its weight won't matter as
		// we have already added the smaller edges and the nodes are already
		// connected
	}
	for(int i=1; i<LOG; i++)
	{
		for(int j=1; j<=n; j++)
		{
			// 2^ith component of j in dsu
			up[j][i] = up[up[j][i-1]][i-1];
			// weight that we need to consider
			weight[j][i] = weight[up[j][i-1]][i-1];
		}
	}
}

int main()
{
    int test, cases = 1;

    scanf("%d", &test);
    while(test--)
    {
    	scanf("%d%d", &n, &m);
    	clear();
    	FOR(i,1,n+1)
    	{
    		scanf("%d", &a[i]);
    		// initializing each node as a single component
    		color[i].insert({a[i],1});
    		best[i] = {1,-a[i]};
    		ans[i].pb({0,a[i]});
    	}

    	int u, v, w;

    	FOR(i,1,m+1)
    	{
    		scanf("%d%d%d", &u, &v, &w);
    		edges.pb({w,u,v});
    	}
    	sort(begin(edges),end(edges));
    	solve();

    	int last = 0, q;
    	scanf("%d", &q);
    	printf("Case #%d:\n", cases++);
    	while(q--)
    	{
    		scanf("%d%d", &u, &w);
    		// the problem used this xor-ing to make the solution online
    		u^=last, w^=last; 
    		// u will be the component we can visit
    		for(int i=LOG-1; i>=0; i--)
    		{
    			if(weight[u][i]<=w)
    				u=up[u][i];
    		}
    		int idx = lower_bound(ALL(ans[u]),pii{w,inf}) - begin(ans[u]) - 1;
    		last = ans[u][idx].second;
    		printf("%d\n", last);
    	}
    	clear();
    }
    return 0;
}