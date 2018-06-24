// Calculate how many numbers in the range from A to B that have digit d in only the even positions and 
// no digit occurs in the even position and the number is divisible by m.


string A, B; int m, d;
ll dp[2002][2002][2][2];

ll calc(int idx, int Mod, bool s, bool b)
{
	if(idx==B.size()) return Mod==0;

	if(dp[idx][Mod][s][b]!=-1)
		return dp[idx][Mod][s][b];

	ll ret=0;

	int low=s ? 0 : A[idx]-'0';
	int high=b ? 9 : B[idx]-'0';

	for(int i=low; i<=high; i++)
	{
		if(idx%2 && i!=d) continue;
		if(idx%2==0 && i==d) continue;

		ret=(ret+calc(idx+1, (Mod*10+i)%m, s || i>low, b || i<high))%mod;

		// if(ret>=mod) ret-=mod;
	}

	return dp[idx][Mod][s][b]=ret;
}

int main()
{
	// ios_base::sync_with_stdio(0); 
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);

	cin>>m>>d>>A>>B;

	ms(dp,-1);

	prnt(calc(0,0,0,0));


	return 0;
}


