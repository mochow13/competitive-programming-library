int n, m, p; // n = # of nodes on left, m = # of nodes on right
vi bp[N]; // bipartite graph
int matched[N], revmatch[N];
bool seen[N], visited[2][N];

bool trymatch(int u)
{
	FOR(j,0,bp[u].size())
	{
		int v=bp[u][j];
		if(seen[v]) continue;

		seen[v]=true;

		// v is on right, u on left
		if(matched[v]<0 || trymatch(matched[v]))
		{
			matched[v]=u;
			revmatch[u]=v;
			return true;
		}
	}

	return false;
}

// 0 based
int maxbpm(int sz)
{
	ms(matched,-1);
	ms(revmatch,-1); // for min-vertex-cover

	int ret=0;

	FOR(i,0,sz)
	{
		ms(seen,false);
		if(trymatch(i)) ret++;
	}

	return ret;
}

void dfsLast(int u, bool side)
{
	if(visited[side][u]) return;
	visited[side][u]=true;

	if(!side)
	{
		for(int i=0; i<n; i++)
		{
			if(graph[u][i] && matched[u]!=i)
				dfsLast(i,1-side);
		}
	}
	else dfsLast(matched[u],1-side);
}

void findMinVertexCover()
{
	FOR(i,0,n)
	{
		if(revmatch[i]==-1)
		{
			dfsLast(i,0);
		}
	}
	// Assuming both sides have n nodes
	vi mvc, mis; // min vertex cover, max independent set	
	FOR(i,0,n)
	{
		if(!visited[0][i] || visited[1][i]) mvc.pb(i);
		if(!(!visited[0][i] || visited[1][i])) mis.pb(i);
	}
}
// The following probably optimizes for large graphs
bool trymatch(int u)
{
	// tag is used so that we don't clear seen each time
	if(seen[u]==tag) return false;
	seen[u]=tag;
	FOR(j,0,bp[u].size())
	{
		int v=bp[u][j];
		// first we only consider any matched[v]==-1 case
		if(matched[v]<0)
		{
			matched[v]=u;
			return true;
		}
	}
	FOR(j,0,bp[u].size())
	{
		int v=bp[u][j];
		// Now we go deeper and call trymatch
		if(trymatch(matched[v]))
		{
			matched[v]=u;
			return true;
		}
	}
	return false;
}