int n, m, x, y, k, a, b, c;
vi Graph[103], Cost[103];
vector<priority_queue<int> > d(103);
priority_queue < pii > Q;

void goDijkstra()
{

	// Here, elements are sorted in decreasing order of the first elements
	// of the pairs and then the second elements if equal first element.

	// d[i] is the priority_queue of the node i where the best k path length
	// will be stored in decreasing order. So, d[i].top() has the longest of the
	// first k shortest path.

	d[x].push(0);	
	Q.push(MP(x,0));	
	// Q contains the nodes in the increasing order of their cost
	// Since the priority_queue sorts the pairs in decreasing order of their
	// first element and then second element, to sort it in increasing order
	// we will negate the cost and push it.

	while(!Q.empty())
	{
		pii t=Q.top(); Q.pop();
		int u=t.first, costU=-t.second;	
		// Since the actual cost was negated.

		FOR(j,0,Graph[u].size())
		{
			int v=Graph[u][j];

			// prnt(v); prnt(d[v].size());

			// Have we already got k shortest paths? Or is the longest path can be made better?
			if(d[v].size()<k || d[v].top()>costU+Cost[u][j])
			{
				int temp=costU+Cost[u][j];
				d[v].push(temp);
				Q.push(MP(v,-temp));
			}
			if(d[v].size()>k) d[v].pop(); 
	// If we have more than k shortest path for the current node, we can pop
	// the worst ones.
		}
	}

	if(d[y].size()<k) prnt(-1); 
	// We have not found k shortest path for our destination.
	else prnt(d[y].top());
}

int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	while(scanf("%d%d", &n, &m) && n+m)
	{
		scanf("%d%d%d", &x, &y, &k);

		FOR(i,0,m)
		{
			scanf("%d%d%d", &a, &b, &c);

			Graph[a].pb(b);
			Cost[a].pb(c);
		}

		goDijkstra();

		FOR(i,0,103) Graph[i].clear(), Cost[i].clear();
		FOR(i,0,103)
		{
			while(!d[i].empty()) d[i].pop();
		}

		while(!Q.empty()) Q.pop();
	}


	return 0;
}






