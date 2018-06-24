class PalindromicTree
{
public:
	int s[MAX], Link[MAX], Len[MAX], Edge[MAX][26];
	int node, lastPal, n;
	ll cnt[MAX];

	void init()
	{
		s[n++]=-1;
		Link[0]=1; Len[0]=0;
		Link[1]=1; Len[1]=-1;
		node=2;
	}

	int getLink(int v)
	{
		while(s[n-Len[v]-2]!=s[n-1]) v=Link[v];
		return v;
	}

	void addLetter(int c)
	{
		// cout<<char(c+'a')<<" "<<n<<endl;

		s[n++]=c;
		lastPal=getLink(lastPal);

		if(!Edge[lastPal][c])
		{
			Len[node]=Len[lastPal]+2;
			Link[node]=Edge[getLink(Link[lastPal])][c];
			cnt[node]++;
			Edge[lastPal][c]=node++;
		}
		else
		{
			cnt[Edge[lastPal][c]]++;
		}

		lastPal=Edge[lastPal][c];
	}

	void clear()
	{
		FOR(i,0,node+1)
		{
			cnt[i]=0;
			ms(Edge[i],0);
		}
		n=0;
		lastPal=0;
	}
} PTA;