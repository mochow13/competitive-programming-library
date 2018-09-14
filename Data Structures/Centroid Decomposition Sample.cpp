/* You are given a tree consisting of n vertices. A number is written on each vertex;
the number on vertex i is equal to a[i].
Let, g(x,y) is the gcd of the numbers written on the vertices belonging to the path from
x to y, inclusive. For i in 1 to 200000, count number of pairs (x,y) (1<=x<=y) such
that g(x,y) equals to i.
Note that 1<=x<=y does not really matter.
*/
vi graph[MAX];
int n, a[MAX], sub[MAX], total, cnt[MAX], cent, upto[MAX];
ll ans[MAX];
bool done[MAX];
set<int> take[MAX];

void dfs(int u, int p)
{
	sub[u] = 1;
	total++;

	for (auto v : graph[u])
	{
		if (v == p || done[v]) continue;
		dfs(v, u);
		sub[u] += sub[v];
	}
}

int getCentroid(int u, int p)
{
	// cout<<u<<" "<<sub[u]<<endl;
	for (auto v : graph[u])
	{
		if (!done[v] && v != p && sub[v] > total / 2)
			return getCentroid(v, u);
	}

	return u;
}

void go(int u, int p, int val)
{
	ans[val]++;
	take[cent].insert(val);
	cnt[val]++;

	for (auto v : graph[u])
	{
		if (!done[v] && v != p)
		{
			go(v, u, upto[v]);
		}
	}
}

void calc(int u, int p, int val)
{
	for (auto it : take[cent])
	{
		int g = gcd(val, it);
		ans[g] += cnt[it];
	}

	for (auto v : graph[u])
	{
		if (!done[v] && v != p)
		{
			calc(v, u, upto[v]);
		}
	}
}

void clean(int u, int p, int val)
{
	cnt[val] = 0;

	for (auto v : graph[u])
	{
		if (!done[v] && v != p)
		{
			clean(v, u, upto[v]);
		}
	}
}

void calcgcd(int u, int p, int val)
{
	upto[u] = val;

	for (auto v : graph[u])
	{
		if (!done[v] && v != p)
		{
			calcgcd(v, u, gcd(val, a[v]));
		}
	}
}

void solve(int u)
{
	total = 0;
	dfs(u, -1);

	cent = getCentroid(u, -1);
	calcgcd(cent, -1, a[cent]);

	// debug("cent",cent);
	done[cent] = true;

	for (auto v : graph[cent])
	{
		if (done[v]) continue;
		// cout<<"from centroid "<<cent<<" going to node: "<<v<<endl;
		calc(v, cent, upto[v]);
		go(v, cent, upto[v]);
	}

	for (auto v : graph[cent])
	{
		if (!done[v])
			clean(v, cent, upto[v]);
	}

	for (auto v : graph[cent])
	{
		if (!done[v])
			solve(v);
	}
}

int main()
{
	// ios_base::sync_with_stdio(0);
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	int test, cases = 1;

	scanf("%d", &n);
	FOR(i, 1, n + 1)
	{
		scanf("%d", &a[i]);
		ans[a[i]]++;
	}

	int u, v;

	FOR(i, 1, n)
	{
		scanf("%d%d", &u, &v);
		graph[u].pb(v);
		graph[v].pb(u);
	}

	solve(1);
	FOR(i, 1, MAX) if (ans[i]) printf("%d %lld\n", i, ans[i]);

	return 0;
}
