// Maximum in a range with lazy propagation.
class SegmentTree
{
public:
	ll Tree[4*MAX], Lazy[4*MAX];
	void pushdown(int node)
	{
		if(Lazy[node])
		{
			Lazy[lc]+=Lazy[node];
			Lazy[rc]+=Lazy[node];
			Tree[lc]+=Lazy[node];
			Tree[rc]+=Lazy[node];
			Lazy[node]=0;
		}
	}

	void build(int node, int l, int r)
	{
		Lazy[node]=0;
		if(l==r)
		{
			Tree[node]=in[l]; // input values
			return;
		}
		int mid=(l+r)/2;
		build(lc,l,mid);
		build(rc,mid+1,r);
		Tree[node]=max(Tree[lc],Tree[rc]);
		Lazy[node]=0;
	}
	// Range update
	void update(int node, int l, int r, int x, int y, ll val)
	{
		// puts("range update");
		if(x>r || y<l) return;
		if(x<=l && r<=y)
		{
			Tree[node]+=val;
			Lazy[node]+=val;
			return;
		}

		if(l!=r) pushdown(node);	

		int mid=(l+r)/2;
		update(lc,l,mid,x,y,val);
		update(rc,mid+1,r,x,y,val);
		Tree[node]=max(Tree[lc],Tree[rc]);
	}
	// Range query
	ll query(int node, int l, int r, int x, int y)
	{
		if(x>r || y<l) return -INF;
		if(x<=l && r<=y) return Tree[node];
		if(l!=r) pushdown(node);

		int mid=(l+r)/2;
		return max(query(lc,l,mid,x,y),query(rc,mid+1,r,x,y));
	}
} segtree;