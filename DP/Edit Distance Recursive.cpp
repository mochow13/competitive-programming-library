int dp[34][34];
string a, b;

int editDistance(int i, int j)
{
	if (dp[i][j]!=-1)
		return dp[i][j];
	if (i==0)
		return dp[i][j]=j;
	if (j==0)
		return dp[i][j]=i;
	
	int cost;
	if (a[i-1]==b[j-1])
		cost=0;
	else
		cost=1;
	return dp[i][j]=min(editDistance(i-1,j)+1,min(editDistance(i,j-1)+1,
					editDistance(i-1,j-1)+cost));
}

int main()
{
	ms(dp,-1);
	cin>>a>>b;
	prnt(editDistance(a.size(),b.size()));
    return 0;
}