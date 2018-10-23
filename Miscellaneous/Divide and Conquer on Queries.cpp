/* You are given an array a[] of size n, an integer m and bunch of queries (l,r).
For each query, you have to answer the number of subsequences of the subarray (a[l]...a[r]) 
whose sum is divisible by m.
*/
const int N = 2 * MAX + 7;
int n, m, a[N];
int input[N][3]; // inputs queries, answer sored in input[i][2]
int dp_left[N][20], dp_right[N][20];
int ans[N];

void solve(int L, int R, vi all)
{
	if(L>R || all.empty()) return;
	// initialize only this range
	FOR(i,L,R+1) FOR(j,0,m) dp_left[i][j] = 0, dp_right[i][j] = 0;

	int mid = (L+R)/2;

	dp_left[mid][0] = 1;
	dp_right[mid-1][0] = 1;
	// calculate the number of subsequences starting from mid-1 to L in dp_left
	for(int i=mid-1; i>=L; i--)
	{
		for(int j=0; j<m; j++)
		{
			int taken = (a[i]+j)%m;

			dp_left[i][taken] = (dp_left[i][taken] + dp_left[i+1][j]) % mod;
			dp_left[i][j] = (dp_left[i][j] + dp_left[i+1][j]) % mod;
		}
	}
	// calculate the number of subsequences starting from mid to R in dp_right
	for(int i=mid; i<=R; i++)
	{
		for(int j=0; j<m; j++)
		{
			int taken = (a[i]+j)%m;

			dp_right[i][taken] = (dp_right[i][taken] + dp_right[i-1][j]) % mod;
			dp_right[i][j] = (dp_right[i][j] + dp_right[i-1][j]) % mod;
		}
	}

	vi ls, rs;
	for(auto idx: all)
	{
		int l = input[idx][0], r = input[idx][1];

		if(l>mid) rs.pb(idx);
		else if(r<mid) ls.pb(idx);
		else
		{
			if(l==r && l==mid) // query is just on mid, specially handled
			{
				ans[idx] = ((a[mid] % m == 0) ? 2: 1);
			}
			else if(l==mid) // starts from mid
			{
				ans[idx] = dp_right[r][0];
			}
			else if(r==mid) // ends in mid
			{
				int rem = a[mid] % m;

				ans[idx] = dp_left[l][0];
				ans[idx] = (ans[idx] + dp_left[l][(m-rem)%m]) % mod;
			}
			else
			{
				// merge both sides and calculate answer for current query
				for(int j=0; j<m; j++)
				{
					ans[idx] = (ans[idx] + (dp_left[l][j] * dp_right[r][(m-j)%m]) % mod) % mod;
				}
			}
		}
	}
	// find answer for other queries by divide and conquer
	solve(L,mid,ls);
	solve(mid+1,R,rs);
}