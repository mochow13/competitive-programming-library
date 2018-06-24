int aux[MAX], b[MAX], n, m, weight[MAX], u, v;
vi graph[MAX];
int parent[MAX][17], st[MAX], en[MAX], tag = 0, dist[MAX], blocSZ;
int go[100005], lca[100005], cnt[MAX], t[MAX];
bool seen[MAX];
struct info
{
	int u, v, id;
	bool fl;
	info() {}
	info(int u, int v, int id, bool fl) : u(u), v(v), id(id), fl(fl) { }
};
vector<info> Q;
// "Unordered"
void compress(int n, int *in, int *out)
{
	unordered_map <int, int> mp;
	for (int i = 1; i <= n; i++) out[i] = mp.emplace(in[i], mp.size()).first->second;
}
void dfs(int u, int p, int d)
{
	parent[u][0] = p;
	st[u] = ++tag;
	dist[u] = d;
	for (auto v : graph[u])
	{
		if (v != p) dfs(v, u, d + 1);
	}
	en[u] = ++tag;
	aux[st[u]] = u;
	aux[en[u]] = u;
}
void sparse()
{
	for (int j = 1; 1 << j < n; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			if (parent[i][j - 1] != -1)
				parent[i][j] = parent[parent[i][j - 1]][j - 1];
		}
	}
}
int query(int p, int q)
{
	if (dist[p] < dist[q]) swap(p, q);
	int x = 1;
	while (true)
	{
		if ((1 << (x + 1)) > dist[p]) break;
		x++;
	}
	FORr(i, x, 0) if (dist[p] - (1 << i) >= dist[q]) p = parent[p][i];
	if (p == q) return p;
	FORr(i, x, 0)
	{
		if (parent[p][i] != -1 && parent[p][i] != parent[q][i])
		{
			p = parent[p][i];
			q = parent[q][i];
		}
	}
	return parent[p][0];
}
int ans = 0;
void doit(int idx)
{
	if (!seen[aux[idx]])
	{
		cnt[b[idx]]++;
		if (cnt[b[idx]] == 1) ans++;
	}
	else
	{
		cnt[b[idx]]--;
		if (cnt[b[idx]] == 0) ans--;
	}
	seen[aux[idx]] ^= 1;
}
int main()
{
	// Each node has some weight associated with it
	// u v : ask for how many different integers that represent the weight of
	// nodes there are on the path from u to v.
	ms(parent, -1);
	scanf("%d%d", &n, &m);
	blocSZ = sqrt(n);
	FOR(i, 1, n + 1)
	{
		scanf("%d", &weight[i]);
	}
	FOR(i, 1, n)
	{
		scanf("%d%d", &u, &v);
		graph[u].pb(v);
		graph[v].pb(u);
	}
	dfs(1, 0, 0);
	sparse();
	compress(n, weight, t);
	(1, 1) << endl;
	FOR(i, 1, 2 * n + 1) b[i] = t[aux[i]];
	FOR(i, 0, m)
	{
		scanf("%d%d", &u, &v);
		lca[i] = query(u, v);
		if (st[u] > st[v]) swap(u, v);
		if (lca[i] == u) Q.pb(info(st[u], st[v], i, 0));
		else Q.pb(info(en[u], st[v], i, 1));
	}
	sort(Q.begin(), Q.end(), [](const info & a, const info & b)->bool
	{
		if (a.u / blocSZ == b.u / blocSZ) return a.v < b.v;
		return a.u < b.u;
	});
	int L = 1, R = 0;
	FOR(i, 0, Q.size())
	{
		int l = Q[i].u, r = Q[i].v, anc = lca[Q[i].id];

		while (R < r)	{ R++; doit(R); }
		while (R > r)	{ doit(R); R--; }
		while (L > l)	{ L--; doit(L); }
		while (L < l)	{ doit(L); L++; }

		if (Q[i].fl)
		{
			if (!cnt[b[st[anc]]])
				go[Q[i].id] = ans + 1;
			else go[Q[i].id] = ans;
		}
		else go[Q[i].id] = ans;
	}
	FOR(i, 0, m) printf("%d\n", go[i]);
	return 0;
}