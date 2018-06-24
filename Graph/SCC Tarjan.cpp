stack<int> st;
vector<vector<int> > scc; 
int low[MAX], disc[MAX], comp[MAX];
int dfs_time;
bool in_stack[MAX];

vi graph[MAX];
int n; // node count indexed from 1

void dfs(int u)
{
	low[u] = dfs_time;
	disc[u] = dfs_time;
	dfs_time++;

	in_stack[u] = true;
	st.push(u);
	
	int sz = graph[u].size(), v;
	for(int i = 0; i < sz; i++)
	{
		v = graph[u][i];
	
		if(disc[v] == -1)
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(in_stack[v] == true)
			low[u] = min(low[u], disc[v]);
	}

	if(low[u] == disc[u])
	{
		scc.push_back(vector<int>());
		while(st.top() != u)
		{
			scc[scc.size() - 1].push_back(st.top());
			in_stack[st.top()] = false;
			st.pop();
		}

		scc[scc.size() - 1].push_back(u);
		in_stack[u] = false;
		st.pop();
	}
}

int tarjan()
{
	memset(comp, -1, sizeof(comp));
	memset(disc, -1, sizeof(disc));
	memset(low, -1, sizeof(low));
	memset(in_stack, 0, sizeof(in_stack));
	dfs_time = 0;

	while(!st.empty())
		st.pop();

	for(int i = 1; i <= n; i++)
		if(disc[i] == -1)
			dfs(i);

	int sz = scc.size();
	for(int i = 0; i < sz; i++)
		for(int j = 0; j < (int)scc[i].size(); j++)
			comp[scc[i][j]] = i;

	return sz;
}
