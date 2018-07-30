int n;
vi graph[MAX], cost[MAX];

struct point {
	int x, y, index;
	bool operator<(const point &p) const { return x == p.x ? y < p.y : x < p.x; }
} p[MAX];

struct node {
	int value, p;
} T[MAX];

struct UnionFind {
	int p[MAX];
	void init(int n) { for (int i = 1; i <= n; i++)  p[i] = i; }
	int find(int u) { return p[u] == u ? u : p[u] = find(p[u]); }
	void Union(int u, int v) { p[find(u)] = find(v); }
} dsu;

struct edge {
	int u, v, c;
	bool operator < (const edge &p) const {
		return c < p.c;
	}
};
vector<edge> edges;

int query(int x) {
	int r = inf, p = -1;
	for (; x <= n; x += (x & -x)) if (T[x].value < r) r = T[x].value, p = T[x].p;
	return p;
}

void modify(int x, int w, int p) {
	for (; x > 0; x -= (x & -x)) if (T[x].value > w) T[x].value = w, T[x].p = p;
}

int dist(point &a, point &b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void add(int u, int v, int c) {
	edges.pb({u, v, c});
}

void kruskal() {
	dsu.init(n);
	SORT(edges);
	for (edge e : edges) {
		int u = e.u, v = e.v, c = e.c;
		// cout<<u<<" "<<v<<" "<<c<<endl;
		if (dsu.find(u) != dsu.find(v)) {
			graph[u].push_back(v);
			graph[v].push_back(u);
			cost[u].push_back(c);
			cost[v].push_back(c);
			dsu.Union(u, v);
		}
	}
}

int manhattan() {
	for (int i = 1; i <= n; ++i) p[i].index = i;
	for (int dir = 1; dir <= 4; ++dir) {
		if (dir == 2 || dir == 4) {
			for (int i = 1; i <= n; ++i) swap(p[i].x, p[i].y);
		} else if (dir == 3) {
			for (int i = 1; i <= n; ++i) p[i].x = -p[i].x;
		}
		sort(p + 1, p + 1 + n);
		vector<int> v; static int a[MAX];
		for (int i = 1; i <= n; ++i) a[i] = p[i].y - p[i].x, v.push_back(a[i]);
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for (int i = 1; i <= n; ++i) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
		for (int i = 1; i <= n; ++i) T[i].value = inf, T[i].p = -1;
		for (int i = n; i >= 1; --i) {
			int pos = query(a[i]);
			if (pos != -1) add(p[i].index, p[pos].index, dist(p[i], p[pos]));
			modify(a[i], p[i].x + p[i].y, i);
		}
	}
}

int main()
{
	int test, cases = 1;

	scanf("%d", &n);

	// points
	FOR(i,1,n+1)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
	}

	manhattan();
	kruskal();

	// graph = manhattan mst adjacency list
	// cost = corresponding cost of edges

	return 0;
}