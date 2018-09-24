// The problem was to find the distance of the farthest node
// from each node. So we try to find such distance considering
// each node as a root.
const int N=10004;
int n, f[N], g[N], ans[N];
vpii graph[N]; vi prefix[N], suffix[N];

void clear()
{
	FOR(i,1,n+1) graph[i].clear(), prefix[i].clear(), suffix[i].clear();
	ms(f,0); ms(g,0); ms(ans,0);
}
void goforgun(int u, int p=-1, int d=0)
{
	if(p==-1) ans[u]=f[u];

	FOR(j,0,graph[u].size())
	{
		int v=graph[u][j].first;
		int w=graph[u][j].second;

		if(v==p) continue;
		// considering that jth child is deleted
		g[u]=max(prefix[u][j],suffix[u][j]);
		// if we are not in root, we also consider the case
		// where parent of u becomes child of u when u is the root
		// d is the cost between the edge (p--u)
		if(p!=-1) g[u]=max(g[p]+d,g[u]);
		// updating answer for v, here we consider the case when v is root
		ans[v]=max(f[v],g[u]+w);
		goforgun(v,u,w);
	}
}
// Precalculate prefix-max and suffix-max values
// max(prefix[u][j],suffix[u][j]) contains the maximum
// value of f[u] if jth child was deleted
void goforfun(int u, int p=-1)
{
	FOR(j,0,graph[u].size())
	{
		int v=graph[u][j].first;
		int w=graph[u][j].second;

		if(v==p) continue;
		goforfun(v,u);

		f[u]=max(f[u],f[v]+w);
	}
	int pref=0, suff=0;
	FOR(j,0,graph[u].size())
	{
		int v=graph[u][j].first;
		int w=graph[u][j].second;
		// important, we want to keep same size but avoid parent
		if(v==p)
		{
			prefix[u].pb(0);
			continue;
		}
		prefix[u].pb(pref);
		pref=max(pref,f[v]+w);
	}
	FORr(j,graph[u].size()-1,0)
	{
		int v=graph[u][j].first;
		int w=graph[u][j].second;
		if(v==p)
		{
			suffix[u].pb(0);
			continue;
		}
		suffix[u].pb(suff);
		suff=max(suff,f[v]+w);
	}
	// Reversing is important
	REVERSE(suffix[u]);
}

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		int u, w;
		FOR(i,2,n+1)
		{
			scanf("%d%d", &u, &w);

			graph[u].pb(MP(i,w));
			graph[i].pb(MP(u,w));
		}
		goforfun(1);
		goforgun(1);
		FOR(i,1,n+1) prnt(ans[i]);
		clear();
	}
      return 0;
}





