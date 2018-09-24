/* This code builds an auxiliary tree from the given vertices to do
further operations. Example problem: CF 613D */

void dfs(int u, int p=0, int d=0)
{
	tin[u]=++t;
	parent[u][0]=p;
	level[u]=d;
	for(auto v: graph[u])
	{
		if(v==p) continue;
		dfs(v,u,d+1);
	}
	tout[u]=t;
}
void cleanup(vi &vtx)
{
	for(auto it: vtx)
	{
		tree[it].clear();
	}
}
bool isancestor(int u, int v) // Check if u is an ancestor of v
{
	return (tin[u]<=tin[v]) && (tout[v]<=tout[u]);
}
// building the auxiliary tree. Nodes are in vtx
void sortbyEntry(vi &vtx)
{
	// Sort by entry time
	sort(begin(vtx), end(vtx), [](int x, int y){
		return tin[x]<tin[y];
	});
}
void release(vi &vtx)
{
	// removing duplicated nodes
	SORT(vtx);
	vtx.erase(unique(begin(vtx),end(vtx)),end(vtx));
}
void buildTree(vi &vtx)
{
	stack<int> st;
	st.push(vtx[0]);
	FOR(i,1,vtx.size())
	{
		while(!isancestor(st.top(),vtx[i]))
			st.pop();
		tree[st.top()].pb(vtx[i]);
		st.push(vtx[i]);
	}
}
int work(vi &vtx)
{
	sortbyEntry(vtx);
	int sz=vtx.size();
	// Finding all the ancestors, there are few of them
	FOR(i,0,sz-1)
	{
		int anc=query(vtx[i],vtx[i+1]);
		vtx.pb(anc);
	}
	release(vtx);
	sortbyEntry(vtx);
	buildTree(vtx);
	// Do necessary operation on the built auxiliary tree
	cleanup(vtx);
	// return result
}	