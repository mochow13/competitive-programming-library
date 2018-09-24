struct MagicComponents {

	struct edge {
		ll u, v, id;
	};

	ll num, n, edges;

	vector<ll> dfs_num, low, vis;
	vector<ll> cuts; // art-vertices
	vector<edge> bridges; // bridge-edges
	vector<vector<edge>> adj; // graph
	vector<vector<edge>> bccs; // all the bccs where bcc[i] has all the edges inside it
	deque<edge> e_stack;

	// Nodes are numberd from 0

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

	//# Make sure to call run before calling this function.
	// Function returns a new graph such that all two connected
	// components are compressed into one node and all bridges
	// in the previous graph are the only edges connecting the
	// components in the new tree.
	// map is an integer array that will store the mapping
	// for each node in the old graph into the new graph. //$
	MagicComponents component_tree(vector<ll>& map) {
		vector<char> vis(edges);
		for (const edge& e : bridges)
			vis[e.id] = true;

		ll num_comp = 0;
		map.assign(map.size(), -1);
		for (ll i = 0; i < n; ++i) {
			if (map[i] == -1) {
				deque<ll> q;
				q.push_back(i);
				map[i] = num_comp;
				while (!q.empty()) {
					ll node = q.front();
					q.pop_front();
					for (const edge& e : adj[node]) {
						if (!vis[e.id] && map[e.v] == -1) {
							vis[e.id] = true;
							map[e.v] = num_comp;
							q.push_back(e.v);
						}
					}
				}
			}
			++num_comp;
		}

		MagicComponents g(num_comp);
		vis.assign(vis.size(), false);
		for (ll i = 0; i < n; ++i) {
			for (const edge& e : adj[i]) {
				if (!vis[e.id] && map[e.v] < map[e.u]) {
					vis[e.id] = true;
					// This is an edge in the bridge tree
					// we can add this edge to a new graph[] and this will
					// be our new tree. We can now do operations on this tree
					g.add_edge(map[e.v], map[e.u]);
				}
			}
		}
		return g;
	}

	//# Make sure to call run before calling this function.
	// Function returns a new graph such that all biconnected
	// components are compressed into one node. Cut nodes will
	// be in multiple components, so these nodes will also have
	// their own component by themselves. Edges in the graph
	// represent components to articulation points
	// map is an integer array that will store the mapping
	// for each node in the old graph into the new graph.
	// Cut points to their special component, and every other node
	// to their specific component. //$
	MagicComponents bcc_tree(vector<ll>& map) {
		vector<ll> cut(n, -1);
		ll size = bccs.size();
		for (const auto& i : cuts)
			map[i] = cut[i] = size++;

		MagicComponents g(size);
		vector<ll> used(n);
		for (ll i = 0; i < bccs.size(); ++i) {
			for (const edge& e : bccs[i]) {
				vector<ll> tmp = {e.u,e.v};
				for (const ll& node : tmp) {
					if (used[node] != i+1) {
						used[node] = i+1;
						if (cut[node] != -1)
							g.add_edge(i, cut[node]);
						else map[node] = i;
					}
				}
			}
		}
		return g;
	}
};
