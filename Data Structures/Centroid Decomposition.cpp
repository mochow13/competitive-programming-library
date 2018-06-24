int n, m, a, b, Table[MAX][20];
set<int> Graph[MAX];
int Level[MAX], nodeCnt, Subgraph[MAX], Parent[MAX], Ans[MAX];
void findLevel(int u)
{
	itrALL(Graph[u], it)
	{
		int v = *it;
		if (v != Table[u][0])
		{
			Table[v][0] = u;
			Level[v] = Level[u] + 1;
			findLevel(v);
		}
	}
}
void Process()
{
	Level[0] = 0;
	ms(Table, -1);
	Table[0][0] = 0;
	findLevel(0);
// debug;
	for (int j = 1; 1 << j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (Table[i][j - 1] != -1)
				Table[i][j] = Table[Table[i][j - 1]][j - 1];
		}
	}
// debug;
}
int findLCA(int p, int q)
{
	if (Level[p] < Level[q]) swap(p, q);
	int x = 1;
	while (true)
	{
		if ((1 << (x + 1)) > Level[p]) break;
		x++;
	}
	FORr(i, x, 0)
	{
		if (Level[p] - (1 << i) >= Level[q])
			p = Table[p][i];
	}
	if (p == q) return p;
	FORr(i, x, 0)
	{
		if (Table[p][i] != -1 && Table[p][i] != Table[q][i])
		{
			p = Table[p][i];
			q = Table[q][i];
		}
	}
	return Table[p][0];
}
int Dist(int a, int b)
{
	return Level[a] + Level[b] - 2 * Level[findLCA(a, b)];
}
void findSubgraph(int u, int parent)
{
	Subgraph[u] = 1;
	nodeCnt++;
	itrALL(Graph[u], it)
	{
		int v = *it;
		if (v == parent) continue;
		findSubgraph(v, u);
		Subgraph[u] += Subgraph[v];
	}
}
int findCentroid(int u, int p)
{
	itrALL(Graph[u], it)
	{
		int v = *it;
		if (v == p) continue;
		if (Subgraph[v] > nodeCnt / 2) return findCentroid(v, u);
	}
	return u;
}
void Decompose(int u, int p)
{
	nodeCnt = 0;
	findSubgraph(u, u);
	int Cent = findCentroid(u, u);
	if (p == -1) p = Cent;
	Parent[Cent] = p;
	itrALL(Graph[Cent], it)
	{
		int v = *it;
		Graph[v].erase(Cent);
		Decompose(v, Cent);
	}
	Graph[Cent].clear();
}
void update(int u)
{
	int x = u;
	while (true)
	{
		Ans[x] = min(Ans[x], Dist(x, u));
		if (x == Parent[x]) break;
		x = Parent[x];
	}
}
int query(int u)
{
	int x = u;
	int ret = INF;
	while (true)
	{
		ret = min(ret, Dist(u, x) + Ans[x]);
		if (x == Parent[x]) break;
		x = Parent[x];
	}
	return ret;
}
int main()
{
// ios_base::sync_with_stdio(0);
// cin.tie(NULL); cout.tie(NULL);
// freopen("in.txt","r",stdin);
// All the nodes are initially blue
// Then by updating, one node is colored red
// Upon query, return the closest red node of the given node
	scanf("%d%d", &n, &m);
	FOR(i, 0, n - 1)
	{
		scanf("%d%d", &a, &b);
		a--, b--;
		Graph[a].insert(b);
		Graph[b].insert(a);
	}
	Process();
// debug;
	Decompose(0, -1);
	FOR(i, 0, n) Ans[i] = INF;
	update(0);
	while (m--)
	{
		int t, x;
		scanf("%d%d", &t, &x);
		x--;
		if (t == 1) update(x);
		else printf("%d\n", query(x));
	}
	return 0;
}