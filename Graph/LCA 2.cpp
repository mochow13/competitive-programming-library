int n, lef[MAX], rig[MAX], dist[MAX], table[2 * MAX][18];
vi graph[MAX], stk;

void dfs(int u, int p, int d)
{
	dist[u] = d;
	lef[u] = rig[u] = stk.size();
	stk.pb(u);
	for (auto v : graph[u])
	{
		if (v == p) continue;
		dfs(v, u, d + 1);
		rig[u] = stk.size();
		stk.pb(u);
	}
}

int lca(int u, int v)
{
	int l = min(lef[u], lef[v]);
	int r = max(rig[u], rig[v]);
	int g = __builtin_clz(r - l + 1) ^ 31;
	return dist[table[l][g]] < dist[table[r - (1 << g) + 1][g]] ?
	       table[l][g] : table[r - (1 << g) + 1][g];
}

void build()
{
	dfs(1, -1, 0);

	for (int i = 0; i < stk.size(); i++) table[i][0] = stk[i];
	for (int j = 1; (1 << j) <= stk.size(); j++)
	{
		for (int i = 0; i + (1 << j) <= stk.size(); i++)
		{
			table[i][j] = (dist[table[i][j - 1]] < dist[table[i + (1 << (j - 1))][j - 1]] ?
			               table[i][j - 1] : table[i + (1 << (j - 1))][j - 1]);
		}
	}
}