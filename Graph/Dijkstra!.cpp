struct road
{
	int u, w;
	road (int a, int b)
	{
		u=a; w=b;
	}
	bool operator < (const road & p) const
	{
		return w>p.w;
	}
};

int d[100], parent[100], start, end;
mvii g, cost;

void dijkstra (int n)
{
	ms(d,INF);
	ms(parent,-1);
	priority_queue <road> Q;
	Q.push(road(start,0));
	d[start]=0;
	while (!Q.empty())
	{
		road t=Q.top();
		Q.pop();
		int u=t.u;
		for (ul i=0; i<g[u].size(); i++)
		{
			int v=g[u][i];
			if (d[u]+cost[u][i]<d[v])
			{
				d[v]=d[u]+cost[u][i];
				parent[v]=u;
				Q.push(road(v,d[v]));
			}
		}
	}
	return;
}

int main()
{
	int n, m, road_out, road_cost, cases=1;
	while (scanf("%d", &n) && n)
	{
		for (int i=1; i<=n; i++)
		{
			cin>>m;
			for (int j=1; j<=m; j++)
			{
				cin>>road_out>>road_cost;
				g[i].pb(road_out);
				cost[i].pb(road_cost);
			}
		}
		scanf("%d%d", &start, &end);
		dijkstra(n);
		//cout<<d[end]<<endl;
		g.clear(); cost.clear();
		int current=end;
		vi path;
		while (current!=start)
		{
			path.pb(parent[current]);
			current=parent[current];
		}
		printf("Case %d: Path = ", cases++);
		for (int j=(int)path.size()-1; j>-1; j--)
			cout<<path[j]<<" ";
		printf("%d; %d second delay\n", end, d[end]);
	}
	return 0;
}
