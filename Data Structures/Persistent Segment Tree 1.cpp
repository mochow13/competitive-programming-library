// Calculate how many distinct values are there in a given range
// Persistent Segment Tree implementation
// Actually used in Codeforces - The Bakery

int n, k, a[MAX], last[MAX], nxt[MAX];
int idx=1;
int Tree[64*MAX], L[64*MAX], R[64*MAX], root[2*MAX], rt[MAX];
int pos[MAX];

void build(int node, int l, int r)
{
	if(l==r)
	{
		Tree[node]=0;
		return;
	}

	L[node]=++idx;
	R[node]=++idx;

	// cout<<node<<" "<<L[node]<<" "<<R[node]<<endl;

	int mid=(l+r)/2;

	build(L[node],l,mid);
	build(R[node],mid+1,r);

	Tree[node]=0;
}

int update(int node, int l, int r, int pos, int val)
{
	int x;
	x=++idx;

	if(l==r)
	{
		Tree[x]=val;
		return x;
	}

	L[x]=L[node]; R[x]=R[node];

	int mid=(l+r)/2;

	if(pos<=mid) L[x]=update(L[x],l,mid,pos,val);
	else R[x]=update(R[x],mid+1,r,pos,val);

	Tree[x]=Tree[L[x]]+Tree[R[x]];

	return x;
}

int query(int node, int l, int r, int x, int y)
{
	if(x>r || y<l) return 0;
	if(x<=l && r<=y) return Tree[node];

	int mid=(l+r)/2;

	int q1=query(L[node],l,mid,x,y);
	int q2=query(R[node],mid+1,r,x,y);

	return q1+q2;
}

int getCost(int l, int mid)
{
	return query(root[rt[mid]],1,n,l,mid);
}

int main()
{
    int test, cases=1;

    scanf("%d%d", &n, &k);

    build(1,1,n);

    root[0]=1;
    int t=1;

    FOR(i,1,n+1)
    {
    	scanf("%d", &a[i]);

    	int k=pos[a[i]];

    	if(!k)
    	{
    		root[t]=update(root[t-1],1,n,i,1);
    		t++;
    	}
    	else
    	{
    		root[t]=update(root[t-1],1,n,k,0);
    		t++;
    		root[t]=update(root[t-1],1,n,i,1);
    		t++;
    	}

    	rt[i]=t-1;
    	pos[a[i]]=i;
    }
    
    return 0;
}

