int n;
string s, p[MAX];
map<char, int> node[MAX];
int root, nnode, link[MAX];
vi ending[MAX], exist[MAX];
// exist[i] has all the ending occurrences of the input strings
void insertword(int idx)
{
	int len = p[idx].size();
	int now = root;
	FOR(i, 0, len)
	{
		if (!node[now][p[idx][i]])
		{
			node[now][p[idx][i]] = ++nnode;
			node[nnode].clear();
		}
		now = node[now][p[idx][i]];
	}
// which strings end in node number 'now'?
	ending[now].pb(idx);
}
void populate(int curr)
{
// Because 'suffix-links'. It links a node with the longest proper suffix
	for (auto it : ending[link[curr]])
		ending[curr].pb(it);
}
void populate(vi &curr, int idx)
{
// So word number it ends in idx-th character of the text
	for (auto it : curr)
	{
		exist[it].pb(idx);
	}
}
void push_links()
{
	queue<int>q;
	link[0] = -1;
	q.push(0);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		itrALL(node[u], it)
		{
			char ch = it->first;
			int v = it->second;
			int j = link[u];
	        // use map.find()
			while (j != -1 && !node[j][ch])
				j = link[j];
			if (j != -1)link[v] = node[j][ch];
			else link[v] = 0;
			q.push(v);
			populate(v);
		}
	}
}

void traverse()
{
	int len = s.size();
	int now = root;
	FOR(i, 0, len)
	{
        // use map.find()
		while (now != -1 && !node[now][s[i]])
			now = link[now];
		if (now != -1) now = node[now][s[i]];
		else now = 0;
		populate(ending[now], i);
	}
}