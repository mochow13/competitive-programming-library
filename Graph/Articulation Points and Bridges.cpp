vi graph[100];
int dfs_num[100], dfs_low[100], parent[100], cnt;
int dfsroot, rootchild;
int art_v[100];

void articulate(int u)
{
	dfs_low[u]=dfs_num[u]=cnt++;
	for (ul j=0; j<graph[u].size(); j++)
	{
		int v=graph[u][j];
		if (dfs_num[v]==-1)
		{
			parent[v]=u;
			if (u==dfsroot)
				rootchild++;
			articulate(v);
			if (dfs_low[v]>=dfs_num[u])
				art_v[u]=true;
			if (dfs_low[v]>dfs_num[u])
				cout<<"Edge "<<u<<" & "<<v<<" is a bridge."<<endl;
			dfs_low[u]=min(dfs_low[u],dfs_low[v]);
		}
		else if (v!=parent[u])
			dfs_low[u]=min(dfs_low[u],dfs_num[v]);
	}
}

int main()
{
	int n, m, u, v;
	cin>>n>>m;
	for (int i=0; i<m; i++)
	{
		cin>>u>>v;
		graph[u].pb(v);
		graph[v].pb(u);
	}
	cnt=0;
	ms(dfs_num,-1);
	for (int i=0; i<n; i++)
	{
		if (dfs_num[i]==-1)
		{
			dfsroot=i;
			rootchild=0;
			articulate(i);
			art_v[dfsroot]=(rootchild>1);
		}
	}
	prnt("Articulation points:");
	for (int i=0; i<n; i++)
	{
		if (art_v[i])
			cout<<"Vertex: "<<i<<endl;
	}
	return 0;
}