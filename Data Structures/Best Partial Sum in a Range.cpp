struct Node
{
	ll bestSum, bestPrefix, bestSuffix, segSum;
	Node()
	{
		bestSum=bestPrefix=bestSuffix=segSum=-INF;
	}
	void merge(Node &l, Node &r)
	{
		segSum=l.segSum+r.segSum;
		bestPrefix=max(l.bestPrefix,r.bestPrefix+l.segSum);
		bestSuffix=max(r.bestSuffix,r.segSum+l.bestSuffix);
		bestSum=max(max(l.bestSum,r.bestSum),l.bestSuffix+r.bestPrefix);
	}
}tree[150005];

void init(int node, int start, int end)
{
	if(start==end)
	{
		tree[node].bestSum=tree[node].segSum=a[start];
		tree[node].bestSuffix=tree[node].bestPrefix=a[start];
		return;
	}
	int left=node<<1;
	int right=left+1;
	int mid=(start+end)>>1;
	init(left,start,mid);
	init(right,mid+1,end);
	tree[node].merge(tree[left],tree[right]);
}
void update(int node, int start, int end, int i, int val)
{
	if(i<start || i>end)
		return;
	if(start>=i && end<=i)
	{
		tree[node].bestSum=tree[node].segSum=val;
		tree[node].bestSuffix=tree[node].bestPrefix=val;
		a[start]=val;
		return;
	}
	int left=node<<1;
	int right=left+1;
	int mid=(start+end)>>1;
	update(left,start,mid,i,val);
	update(right,mid+1,end,i,val);
	tree[node].merge(tree[left],tree[right]);
}
Node query(int node, int start, int end, int i, int j)
{
	if(i>end || j<start)
		return Node();
	if(start>=i && end<=j)
	{
		return tree[node];
	}
	int left=node<<1;
	int right=left+1;
	int mid=(start+end)>>1;
	Node l=query(left,start,mid,i,j);
	Node r=query(right,mid+1,end,i,j);
	Node n;
	n.merge(l,r);
	return n;
}
