// Query 1: From u to v, print the index of the minimum k numbers,
// and these numbers are removed
// Query 2: Add a value to the subtree of node v
int n, m, q;
int parent[MAX], depth[MAX], subsize[MAX], st[MAX], at[MAX];
int nxt[MAX], chain[MAX], pos, cnt;
ll in[MAX], aux[MAX];
int chainsz[MAX], head[MAX];
vi graph[MAX];
vector<ll> girls[MAX];

class SegmentTree
{
public:
	pair<ll,int> Tree[4*MAX];
	ll Lazy[4*MAX];
	void build(int node, int l, int r)
	{
		Lazy[node]=0;
		if(l==r)
		{
			Tree[node]={aux[l],at[l]};
			return;
		}
		int mid=(l+r)/2;
		build(lc,l,mid);
		build(rc,mid+1,r);
		Tree[node]=min(Tree[lc],Tree[rc]);
	}
	void pushdown(int node)
	{
		if(Lazy[node])
		{
			Lazy[lc]+=Lazy[node];
			Lazy[rc]+=Lazy[node];
			Tree[lc].first+=Lazy[node];
			Tree[rc].first+=Lazy[node];
			Lazy[node]=0;
		}
	}
	void update(int node, int l, int r, int x, int y, ll val)
	{
		if(x>r || y<l) return;
		if(x<=l && r<=y)
		{
			Tree[node].first+=val;
			Lazy[node]+=val;
			return;
		}

		if(l!=r) pushdown(node);	

		int mid=(l+r)/2;
		update(lc,l,mid,x,y,val);
		update(rc,mid+1,r,x,y,val);
		Tree[node]=min(Tree[lc],Tree[rc]);
	}
	pair<ll,int> query(int node, int l, int r, int x, int y)
	{
		if(x>r || y<l) return {INF,inf};
		if(x<=l && r<=y) return Tree[node];
		if(l!=r) pushdown(node);

		int mid=(l+r)/2;
		return min(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
	}
} segtree;

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
		at[pos]=u;
		st[u]=pos++; // Flatening nodes in order of heavy edges!
		aux[st[u]]=in[u];
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
	pair<ll,int> query(int u, int v)
	{
		pair<ll,int> ret={INF,inf};

		while(chain[u]!=chain[v])
		{
			if(depth[head[chain[u]]]<depth[head[chain[v]]])
				swap(u,v);
			int start=head[chain[u]];
			ret=min(ret,segtree.query(1,1,n,st[start],st[u]));
			u=parent[start];
		}

		if(depth[u]>depth[v]) swap(u,v);
		ret=min(ret,segtree.query(1,1,n,st[u],st[v]));
		return ret;
	}
} hld;

void handle(int u, int v, int k)
{
	vi ans;
	while(k--)
	{
		auto out=hld.query(u,v);
		if(out.first>=INF) break;
		// The node which has current minimum weight of a girl
		int idx=out.second;
		ll last=girls[idx].back();
		ans.pb(last);
		girls[idx].pop_back();
		segtree.update(1,1,n,st[idx],st[idx],abs(girls[idx].back()-last));
	}
	printf("%d ", (int)ans.size());
	FOR(i,0,ans.size()) printf("%d ", ans[i]);
	puts("");
}

int main()
{
      int test, cases = 1;
      scanf("%d%d%d", &n, &m, &q);
      int u, v;
      FOR(i,0,n-1)
      {
      	scanf("%d%d", &u, &v);
      	graph[u].pb(v);
      	graph[v].pb(u);
      }
      FOR(i,1,m+1)
      {
      	scanf("%d", &pos);
      	// Girl i is in node i, same node can have multiple girls
      	// Initial weight of each girl equals her index
      	girls[pos].pb(i);
      }

      FOR(i,1,n+1) girls[i].pb(INF);
      FOR(i,1,n+1)
      {
		REVERSE(girls[i]);
		in[i]=girls[i].back();
      }
      hld.init(n);
      hld.dfs(1);
      hld.decompose(1);
      segtree.build(1,1,n);
      while(q--)
      {
      	int t, k;
      	scanf("%d", &t);
      	if(t==1)
      	{
      		scanf("%d%d%d", &u, &v, &k);
      		handle(u,v,k);
      	}
      	else
      	{
      		scanf("%d%d", &v, &k);
      		segtree.update(1,1,n,st[v],st[v]+subsize[v]-1,k);
      	}
      }      
      return 0;
}





