struct info
{
	int l, r, id;
	info(){}
	info(int l, int r, int id) : l(l), r(r), id(id){}
};

int n, t, a[2*MAX];
info Q[2*MAX];
int Block, cnt[1000004];
ll ans=0;
ll Ans[2*MAX];

// always constant
// Farther improvement: When dividing the elements into blocks, we may sort the first block in the 
// ascending order of right borders, the second — in descending, the third — in ascending order again, and so on.

// inline bool comp(const info &a, const info &b)
// {
//     if(a.l/blockSZ!=b.l/blockSZ)
//         return a.l<b.l;
//     if((a.l/blockSZ)&1)
//         return a.r<b.r;
//     return a.r>b.r;
// }

inline bool comp(const info &a, const info &b)
{
	if(a.l/Block==b.l/Block) return a.r<b.r;
	return a.l<b.l;
}

inline void Add(int idx)
{
	ans+=(2*cnt[a[idx]]+1)*a[idx];
	cnt[a[idx]]++;

	/* Actual meaning of the above code
	
	ans-=cnt[a[idx]]*cnt[a[idx]]*a[idx];
	cnt[a[idx]]++;
	ans+=cnt[a[idx]]*cnt[a[idx]]*a[idx];
	
	*/
}

inline void Remove(int idx)
{
	ans-=(2*cnt[a[idx]]-1)*a[idx];
	cnt[a[idx]]--;

	/* Actual meaning of the above code
	
	ans-=cnt[a[idx]]*cnt[a[idx]]*a[idx];
	cnt[a[idx]]--;
	ans+=cnt[a[idx]]*cnt[a[idx]]*a[idx];
	
	*/
}

int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	// Problem: For each query, find the value cnt[a[i]]*cnt[a[i]]*a[i]

	scanf("%d%d", &n, &t);

	Block=sqrt(n);

	FOR(i,1,n+1) a[i]=getnum();

	FOR(i,0,t)
	{
		Q[i].l=getnum();
		Q[i].r=getnum();
		Q[i].id=i;
	}

	sort(Q,Q+t,comp);

	int Left=0, Right=-1;

	FOR(i,0,t)
	{
		while(Left<Q[i].l)
		{
			Remove(Left);
			Left++;
		}
		while(Left>Q[i].l)
		{
			Left--;
			Add(Left);
		}
		while(Right<Q[i].r)
		{
			Right++;
			Add(Right);
		}
		while(Right>Q[i].r)
		{
			Remove(Right);
			Right--;
		}

		Ans[Q[i].id]=ans;
	}

	FOR(i,0,t) printf("%lld\n", Ans[i]);

	return 0;
}