/* You are given a text t and a pattern p. For each index of t, find
how many proper prefixes of p ends in this position. Similarly, find how many proper
suffixes start from this position.
While calculating the failure function, we can find for each position of the pattern p
how many of its own prefixes end in that position. After calculating that in dp[i],
we can just feel table[i] for text t.
*/

int pi[N], dp[N];
void prefixFun(string &p)
{
	int now;
	pi[0]=now=-1;

	dp[0]=1; // 0th character is a prefix ending in itself, base case

	for(int i=1; i<p.size(); i++)
	{
		while(now!=-1 && p[now+1]!=p[i])
			now=pi[now];

		if(p[now+1]==p[i]) pi[i]=++now;
		else pi[i]=now=-1;

		if(pi[i]!=-1) // calculate the # of prefixes end in this position of p
			dp[i]=dp[pi[i]]+1; 
		else dp[i]=1;
	}
}

int kmpMatch(string &p, string &t, int *table)
{
	int now=-1;
	FOR(i,0,t.size())
	{
		while(now!=-1 && p[now+1]!=t[i])
			now=pi[now];
		if(p[now+1]==t[i]) 
		{
			++now;
			table[i]=dp[now]; // table for text t
		}
		else now=-1;
		if(now+1==p.size()) 
		{
			now=pi[now];
		}
	}
}
