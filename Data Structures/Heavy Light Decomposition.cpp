int parent[MAX], depth[MAX], subsize[MAX];
int nxt[MAX], chain[MAX], st[MAX], pos, cnt;
int chainsz[MAX], head[MAX];
vi graph[MAX];

class HLD
{
public:
	void init(int n)
	{
		for(int i=0; i<=n; i++) nxt[i]=-1, chainsz[i]=0;
		cnt=pos=1;
	}
	void dfs(int u, int p=-1, int d=0)
	{
		parent[u]=p;
		subsize[u]=1;
		depth[u]=d;

		for(auto v: graph[u])
		{
			if(v==p) continue;
			dfs(v,u,d+1);
			subsize[u]+=subsize[v];

			if(nxt[u]==-1 || subsize[v]>subsize[nxt[u]])
				nxt[u]=v;
		}
	}
	void decompose(int u, int p=-1)
	{
		chain[u]=cnt-1;
		// May need to update in segment tree on pos with some val[u]
		st[u]=pos++;
		// Take the node value to corresponding position
		// val[st[u]]=(ll)c[u]*a+b;
		if(!chainsz[cnt-1]) head[cnt-1]=u;
		chainsz[cnt-1]++;

		if(nxt[u]!=-1) decompose(nxt[u],u);

		for(auto v: graph[u])
		{
			if(v==p || v==nxt[u]) continue;
			++cnt;
			decompose(v,u);
		}
	}
	void update(int u, int v, ll add) 
	{
		while(chain[u]!=chain[v])
		{
			if(depth[head[chain[u]]]<depth[head[chain[v]]])
				swap(u,v);
			int start=head[chain[u]];
			segtree.update(1,1,n,st[start],st[u],add);
			u=parent[start];
		}
		if(depth[u]>depth[v]) swap(u,v);
		segtree.update(1,1,n,st[u],st[v],add);
	}

	int query(int u, int v)
	{
		int ret=0;
		while(chain[u]!=chain[v])
		{
			if(depth[head[chain[u]]]<depth[head[chain[v]]])
				swap(u,v);
			int start=head[chain[u]];
			// query on respective ds
			ret+=bit.query(st[start],st[u]);
			u=parent[start];
		}

		if(depth[u]>depth[v]) swap(u,v);
		ret+=bit.query(st[u],st[v]);

		return ret;
	}
} hld;