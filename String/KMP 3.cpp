string p, t;
int pi[MAX], cnt[MAX];

void prefixFun()
{
	int now;
	pi[0]=now=-1;

	for(int i=1; i<p.size(); i++)
	{
		while(now!=-1 && p[now+1]!=p[i])
			now=pi[now];

		if(p[now+1]==p[i]) pi[i]=++now;
		else pi[i]=now=-1;
	}
}

int kmpMatch()
{
	int now=-1;
	FOR(i,0,t.size())
	{
		cout<<"now: "<<i<<" "<<now<<endl;	
		while(now!=-1 && p[now+1]!=t[i])
			now=pi[now];
		if(p[now+1]==t[i]) 
		{
			++now;
			cnt[now]++;
		}
		else now=-1;
		if(now+1==p.size()) 
		{
			// match found
			// cout<<"match and setting "<<now<<" to "<<pi[now]<<endl;
			now=pi[now]; // match again
		}
	}
}

int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	cin>>t>>p;

	prefixFun();
	FOR(i,0,p.size()) cout<<pi[i]<<" "; cout<<endl;
	prnt(kmpMatch());
	FOR(i,0,p.size()) cout<<cnt[i]<<" "; cout<<endl;
	FORr(i,p.size()-1,0)
	{
		if(pi[i]==-1) continue;
		cnt[pi[i]]+=cnt[i];
	}
	FOR(i,0,p.size()) cout<<cnt[i]<<" "; cout<<endl;

	return 0;
}



