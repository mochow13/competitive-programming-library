/*
Feasible flow in network with upper + lower constraint, no source, no sink:
cap' = upper bound - lower bound.
Add source s, sink t.
Let M[v] = (sum of lowerbounds of ingoing edges to v) - (sum of lower bounds of outgoing edges from v).
For all v, if M[v] > 0, add (s, v, M), else add (v, t, -M).
If all outgoing edges from S are full --> feasible flow exists, it is flow + lower bounds.

Max flow with both upper + lower constraints, source s, sink t: add edge (t, s, +INF).
Binary search lower bound, check whether feasible flow exists WITHOUT source / sink

*/

struct Edge
{
	int to, rev, f, cap;
};


class Dinic
{
public:

	int dist[MAX], q[MAX], work[MAX], src, dest;
	vector<Edge> graph[MAX];
	// MAX equals to node_number

	void init(int sz)
	{
		FOR(i,0,sz+1) graph[i].clear();
	}

	void clearFlow(int sz)
	{
		FOR(i,0,sz+1)
		{
			FOR(j,0,graph[i].size())
				graph[i][j].f=0;
		}
	}

	void addEdge(int s, int t, int cap)
	{
		Edge a={t,(int)graph[t].size(),0,cap};
		Edge b={s,(int)graph[s].size(),0,0};

		// If our graph has bidirectional edges
		// Capacity for the Edge b will equal to cap
		// For directed, it is 0

		graph[s].emplace_back(a);
		graph[t].emplace_back(b);
	}

	bool bfs()
	{
		ms(dist,-1);
		dist[src]=0;
		int qt=0;
		q[qt++]=src;

		for(int qh=0; qh<qt; qh++)
		{
			int u=q[qh];

			for(auto &e: graph[u])
			{
				int v=e.to;

				if(dist[v]<0 && e.f<e.cap)
				{
					dist[v]=dist[u]+1;
					q[qt++]=v;
				}
			}
		}

		return dist[dest]>=0;
	}

	int dfs(int u, int f)
	{
		if(u==dest) return f;

		for(int &i=work[u]; i<(int)graph[u].size(); i++)
		{
			Edge &e=graph[u][i];

			if(e.cap<=e.f) continue;

			int v=e.to;

			if(dist[v]==dist[u]+1)
			{
				int df=dfs(v,min(f,e.cap-e.f));

				if(df>0)
				{
					e.f+=df;
					graph[v][e.rev].f-=df;

					return df;
				}
			}
		}

		return 0;
	}

	int maxFlow(int _src, int _dest)
	{
		src=_src;
		dest=_dest;

		int result=0;

		while(bfs())
		{
			// debug;
			fill(work,work+MAX,0);
			while(int delta=dfs(src,INF))
				result+=delta;
		}

		return result;
	}
};
