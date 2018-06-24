struct info
{
	int x, ymin, ymax, type;
	info(){}
	info(int x, int ymin, int ymax, int type) : 
		x(x), ymin(ymin), ymax(ymax), type(type) { }

	bool operator < (const info &p) const
	{
		return x<p.x;
	}
};

vector<info> in;
int n, x, y, p, q, m;
vi take;
int Lazy[4*MAX], Tree[4*MAX];

void update(int node, int l, int r, int ymin, int ymax, int val)
{
	if(take[l]>ymax || take[r]<ymin) return;

	if(ymin<=take[l] && take[r]<=ymax)
	{
		Lazy[node]+=val;

		if(Lazy[node]) Tree[node]=take[r]-take[l];
		else Tree[node]=Tree[lc]+Tree[rc];

		return;
	}

	if(l+1>=r) return;

	int mid=(l+r)/2;

	update(lc,l,mid,ymin,ymax,val);
	update(rc,mid,r,ymin,ymax,val);

	if(Lazy[node]) Tree[node]=take[r]-take[l];
	else Tree[node]=Tree[lc]+Tree[rc];
}

ll solve()
{
	take.clear(); ms(Tree,0); ms(Lazy,0);
	take.pb(-1);

	FOR(i,0,in.size())
	{
		take.pb(in[i].ymin);
		take.pb(in[i].ymax);
	}

	SORT(take);
	take.erase(unique(ALL(take)),take.end());
	m=take.size()-1;

	// VecPrnt(take);

	update(1,1,m,in[0].ymin,in[0].ymax,in[0].type);

	int prv=in[0].x; ll ret=0;

	FOR(i,1,in.size())
	{
		ret+=(ll)(in[i].x-prv)*Tree[1];
		prv=in[i].x;
		update(1,1,m,in[i].ymin,in[i].ymax,in[i].type);
	}

	return ret;
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(NULL); cout.tie(NULL);
    // freopen("in.txt","r",stdin);

    int test, cases=1;

    scanf("%d", &test);

    while(test--)
    {
    	scanf("%d", &n);

    	in.clear();

    	FOR(i,0,n)
    	{
	    	scanf("%d%d%d%d", &x, &y, &p, &q);
	 
	    	in.pb(info(x,y,q,1));
	    	in.pb(info(p,y,q,-1));
	    }

    	SORT(in);

    	ll ans=solve();

    	printf("Case %d: %lld\n", cases++, ans);
    }

    return 0;
}

