char text[MAX], patt[MAX];
int pi[MAX], n, m;

void Process()
{
	int now=-1;
	pi[0]=-1;

	for(int i=1; i<m; i++)
	{
		while(now!=-1 && patt[now+1]!=patt[i])
			now=pi[now];
		if(patt[now+1]==patt[i]) pi[i]=++now;
		else pi[i]=now=-1;
	}
}

void Search()
{
	int now=-1;

	for(int i=0; i<n; i++)
	{
		while(now!=-1 && patt[now+1]!=text[i])
			now=pi[now];
		if(patt[now+1]==text[i]) ++now;
		else now=-1;
		if(now==m-1) 
		{
			cout<<"match at "<<i-now<<endl;
			now=pi[now]; // match again
		}
	}
}

int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	cin>>text>>patt;

	n=strlen(text); m=strlen(patt);

	Process();
	Search();

	// FOR(i,0,m) cout<<pi[i]<<" "; cout<<endl;

	return 0;
}