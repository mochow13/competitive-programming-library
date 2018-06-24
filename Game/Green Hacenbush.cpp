// Green Hackenbush
vi graph[505];
int go(int u, int p)
{
	int ret = 0;
	for (auto &v : graph[u])
	{
		if (v == p) continue;
		ret ^= (go(v, u) + 1);
	}
	return ret;
}
int u, v, n;
int main()
{
// ios_base::sync_with_stdio(0);
// cin.tie(NULL); cout.tie(NULL);
// freopen("in.txt","r",stdin);
	int test, cases = 1;
	cin >> test;
	while (test--)
	{
		cin >> n;
		FOR(i, 0, n - 1)
		{
			cin >> u >> v;
			graph[u].pb(v);
			graph[v].pb(u);
		}
		if (go(1, 0)) puts("Alice");
		else puts("Bob");
		FOR(i, 1, n + 1) graph[i].clear();
	}
	return 0;
}