const int MAXN = (1 << 20);
const int MAXLOG = 20;

struct sparse_table
{
	int dp[MAXN][MAXLOG];
	int prec_lg2[MAXN], n;

	sparse_table() { memset(dp, 0, sizeof(dp)); memset(prec_lg2, 0, sizeof(prec_lg2)); n = 0; }

	void init(vector<int> &a)
	{
		n = a.size();
		for(int i = 2; i < 2 * n; i++) prec_lg2[i] = prec_lg2[i >> 1] + 1;
		for(int i = 0; i < n; i++) dp[i][0] = a[i];
		for(int j = 1; (1 << j) <= n; j++)    
			for(int i = 0; i < n; i++)
				dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
	}

	int query(int l, int r) 
	{
		int k = prec_lg2[r - l + 1];
		return min(dp[l][k], dp[r - (1 << k) + 1][k]);
	}
};