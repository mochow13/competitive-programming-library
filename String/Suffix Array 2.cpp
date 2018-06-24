// You are given two strings A and B, consisting only of lowercase letters from the English alphabet. 
// Count the number of distinct strings S, which are substrings of A, but not substrings of B

LL substr_count(int n,char *s)
{
	VI cnt(128);
	for(int i=0;i<n;i++)
		cnt[s[i]]++;
	for(int i=1;i<128;i++)
		cnt[i]+=cnt[i-1];
	VI p(n);
	for(int i=0;i<n;i++)
		p[--cnt[s[i]]]=i;
	VVI c(1,VI(n));
	int w=0;
	for(int i=0;i<n;i++)
	{
		if(i==0 || s[p[i]]!=s[p[i-1]]) w++;
		c[0][p[i]] = w-1;
	}

	for(int k=0,h=1;h<n;k++,h*=2)
	{
		VI pn(n);
		for(int i=0;i<n;i++) {
			pn[i] = p[i] - h;
			if(pn[i]<0) pn[i] += n;
		}
		VI cnt(w,0);
		for(int i=0;i<n;i++)
			cnt[c[k][pn[i]]]++;
		for(int i=1;i<w;i++)
			cnt[i]+=cnt[i-1];
		for(int i=n;i--;)
			p[--cnt[c[k][pn[i]]]]=pn[i];
		w=0;
		c.push_back(VI(n));
		for(int i=0;i<n;i++)
		{
			if(i==0 || c[k][p[i]] != c[k][p[i-1]]) {
				w++; 
			} else {
				int i1 = p[i]   + h; if(i1>=n) i1-=n;
				int i2 = p[i-1] + h; if(i2>=n) i2-=n;
				if(c[k][i1]!=c[k][i2]) w++;
			}
			c[k+1][p[i]] = w-1;
		}
	}

	LL ans = LL(n)*(n-1)/2;
	for(int k=1;k<n;k++)
	{
		int i=p[k];
		int j=p[k-1];
		int cur = 0;
		for (int h=c.size(); h--;)
			if (c[h][i] == c[h][j]) {
				cur += 1<<h;
				i += 1<<h;
				j += 1<<h;
			}
		ans-=cur;
	}
	return ans;
}

char s[200005];
int n, m;

void input()
{
	scanf("%s", s);

	n=strlen(s)+1;
	s[n-1]='a'-1;

	scanf("%s", s+n);
	m=strlen(s+n)+1;

	s[n+m-1]='a'-2;
	s[n+m]=0;
}

void solve()
{
	ll p=substr_count(n,s);
	ll r=substr_count(m,s+n);
	ll q=substr_count(n+m,s)-(ll)n*m;

	// cout<<p<<" "<<r<<" "<<q<<endl;

	ll t=q-p-r;

	t=abs(t);

	prnt(p-t); 
}

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(NULL); cout.tie(NULL);
    // freopen("in.txt","r",stdin);

    int test, cases=1;

    input();
    solve();

    return 0;
}

