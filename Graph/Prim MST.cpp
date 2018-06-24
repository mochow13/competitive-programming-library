vector <ll> graph[10003], cost[10003];
bool visited[10003];
ll d[10003];
int n, m;

int minKey()
{
	ll mini=INF;
	int minidx;
	for (int i=1; i<=n; i++)
	{
		if (!visited[i] && d[i]<mini)
			mini=d[i], minidx=i;
	}
	return minidx;
}

ll Prim()
{
	FOR(i,0,10003)
	{
		d[i]=INF;
		visited[i]=false;
	}
	d[1]=0;
	for (int i=1; i<=n-1; i++)
	{
		int u=minKey();
		visited[u]=true;
		FOR(j,0,graph[u].size())
		{
			int v=graph[u][j];
			if(!visited[v] && cost[u][j]<d[v])
				d[v]=cost[u][j];
		}

	}
	ll ret=0;
	FOR(j,1,n+1)
	{
		// cout<<d[j]<<endl;
		if(d[j]!=INF)
			ret+=d[j];
	}
	return ret;
}

int main()
{
	int a, b, c;
	scanf("%d%d", &n, &m);
	FOR(i,0,m)
	{
		scanf("%d%d%d", &a, &b, &c);
		graph[a].pb(b);
		graph[b].pb(a);
		cost[a].pb(c);
		cost[b].pb(c);
	}
	cout<<Prim()<<endl;

    return 0;
}

