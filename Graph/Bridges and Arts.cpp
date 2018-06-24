struct MagicComponents {

	struct edge {
		ll u, v, id;
	};

	ll num, n, edges;

	vector<ll> dfs_num, low, vis;
	vector<ll> cuts; // art-vertices
	vector<edge> bridges; // bridges
	vector<vector<edge>> adj; // graph
	vector<vector<edge>> bccs; // contains the bccs, each bccs[i] contiains all the edges in a bcc
	deque<edge> e_stack;

	MagicComponents(const ll& _n) : n(_n) {
		adj.assign(n, vector<edge>());
		edges = 0;
	}

	void add_edge(const ll& u, const ll& v) {
		adj[u].push_back({u,v,edges});
		adj[v].push_back({v,u,edges++});
	}

	void run(void) {
		vis.assign(n, 0);
		dfs_num.assign(n, 0);
		low.assign(n, 0);
		bridges.clear();
		cuts.clear();
		bccs.clear();
		e_stack = deque<edge>();
		num = 0;

		for (ll i = 0; i < n; ++i) {
			if (vis[i]) continue;
			dfs(i, -1);
		}
	}

	void dfs(const ll& node, const ll& par) {
		dfs_num[node] = low[node] = num++;
		vis[node] = 1;
		ll n_child = 0;
		for (edge& e : adj[node]) {
			if (e.v == par) continue;
			if (vis[e.v] == 0) {
				++n_child;
				e_stack.push_back(e);
				dfs(e.v, node);

				low[node] = min(low[node], low[e.v]);
				if (low[e.v] >= dfs_num[node]) {
					if (dfs_num[node] > 0 || n_child > 1)
						cuts.push_back(node);
					if (low[e.v] > dfs_num[node]) {
						bridges.push_back(e);
						pop(node);
					} else pop(node);
				}
			} else if (vis[e.v] == 1) {
				low[node] = min(low[node], dfs_num[e.v]);
				e_stack.push_back(e);
			}
		}
		vis[node] = 2;
	}

	void pop(const ll& u) {
		vector<edge> list;
		for (;;) {
			edge e = e_stack.back();
			e_stack.pop_back();
			list.push_back(e);
			if (e.u == u) break;
		}
		bccs.push_back(list);
	}
};