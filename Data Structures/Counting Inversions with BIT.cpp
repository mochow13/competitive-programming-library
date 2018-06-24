ll tree[200005];
int n, a[200005], b[200005];

void update(int idx, ll x)
{
	while(idx<=n)
	{
		tree[idx]+=x;
		idx+=(idx&-idx);
	}
}

int query(int idx)
{
	ll sum=0;
	while(idx>0)
	{
		sum+=tree[idx];
		idx-=(idx&-idx);
	}
	return sum;
}



int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL); // No 'endl'
	// freopen("in.txt","r",stdin);
	int test;
	// cin>>test;
	scanf("%d", &test);
	while(test--)
	{
		ms(tree,0);
		scanf("%d", &n);
		FOR(i,1,n+1) 
		{
			scanf("%d", &a[i]); 
			b[i]=a[i];
		}

		sort(b+1,b+n+1);

		// Compressing the array
		FOR(i,1,n+1)
		{
			int rank=int(lower_bound(b+1,b+1+n,a[i])-b-1);
			a[i]=rank+1;
		}
		// FOR(i,1,n+1) cout<<a[i]<<" "; cout<<endl;
		ll ans=0;
		FORr(i,n,1)
		{
			ans+=query(a[i]-1);
			update(a[i],1);
		}		
		// prnt(ans);
		printf("%lld\n",ans);
	}	


	return 0;
}






