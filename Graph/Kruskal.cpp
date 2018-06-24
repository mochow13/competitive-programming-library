struct edge
{
	int u, v, w;
	bool operator < (const edge & p) const
	{
		return w < p.w;
	}
};
edge get;
int parent[100];
vector <edge> e;
int find(int r)
{
	if (parent[r] == r)
		return r;
	return parent[r] = find(parent[r]);
}
int mst(int n)
{
	sort(e.begin(), e.end());
	for (int i = 1; i <= n; i++)
		parent[i] = i;
	int cnt = 0, s = 0;
	for (int i = 0; i < (int)e.size(); i++)
	{
		int u = find(e[i].u);
		int v = find(e[i].v);
		if (u != v)
		{
			parent[u] = v;
			cnt++;
			s += e[i].w;
			if (cnt == n - 1)
				break;
		}
	}
}