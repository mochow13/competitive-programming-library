/*
You are given a rooted tree with root in vertex 1. Each vertex is coloured in some colour.
Let's call colour c dominating in the subtree of vertex v if there are no other colours 
that appear in the subtree of vertex v more times than colour c. 
So it's possible that two or more colours will be dominating in 
the subtree of some vertex. The subtree of vertex v is the vertex v 
and all other vertices that contains vertex v in each path to the root.
For each vertex v find the sum of all dominating colours in the subtree of vertex v.
*/

int u, v, n, color[MAX], parent[MAX];
vi graph[MAX];
map<int, int> inNode[MAX];
int mxCnt[MAX]; ll sum[MAX], out[MAX];

void merge(int u, int v)
{
	// ***Important: swapping parents
	if (inNode[parent[u]].size() < inNode[parent[v]].size())
		swap(parent[u], parent[v]);

	for (auto it : inNode[parent[v]])
	{
		int f = it.first, s = it.second;

		inNode[parent[u]][f] += s;

		if (inNode[parent[u]][f] > mxCnt[parent[u]])
		{
			mxCnt[parent[u]] = inNode[parent[u]][f];
			sum[parent[u]] = f;
		}
		else if (inNode[parent[u]][f] == mxCnt[parent[u]])
		{
			sum[parent[u]] += f;
		}
	}

	inNode[parent[v]].clear();
}

void dfs(int u, int p)
{
	for (auto v : graph[u])
	{
		if (p == v) continue;
		dfs(v, u);
		merge(u, v);
	}

	out[u] = sum[parent[u]];
}

int main()
{
	ios_base::sync_with_stdio(0);
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	int test, cases = 1;

	n = getnum();

	FOR(i, 1, n + 1)
	{
		color[i] = getnum();
		parent[i] = i;
		inNode[i][color[i]] = 1;
		sum[i] = color[i];
		mxCnt[i] = 1;
	}

	FOR(i, 1, n)
	{
		u = getnum();
		v = getnum();
		graph[u].pb(v);
		graph[v].pb(u);
	}

	dfs(1, 0);

	FOR(i, 1, n + 1) printf("%lld ", out[i]); puts("");

	return 0;
}