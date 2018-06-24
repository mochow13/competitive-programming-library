// For each case, output the case number and the number of integers in the range [A, B] which are
// divisible by K and the sum of its digits
// is also divisible by K.
int k, cases = 1;
ll dp[11][2][83][83];
int visited[11][2][83][83], flag;
string toString(int x)
{
	string temp = "";
	if (x == 0) return "0";
	while (x > 0)
	{
		int r = x % 10;
		temp = char(r + '0') + temp;
		x /= 10;
	}
	return temp;
}
ll calc(int idx, bool low, int modVal, int sumMod, string s)
{
	if (idx == s.size()) return (!modVal && !sumMod);
	if (visited[idx][low][modVal][sumMod] == flag)
		return dp[idx][low][modVal][sumMod];
	visited[idx][low][modVal][sumMod] = flag;
	int digit = low ? 9 : (s[idx] - '0');
	ll ret = 0;
	for (int i = 0; i <= digit; i++)
	{
		ret += calc(idx + 1, low || i < s[idx] - '0', (modVal * 10 + i) % k, (sumMod + i) % k, s);
	}
	return dp[idx][low][modVal][sumMod] = ret;
}
int main()
{
	int test;
	int a, b;
	cin >> test;
	while (test--)
	{
		cin >> a >> b >> k;
		if (k > 90)
		{
			cout << "Case " << cases++ << ": 0" << endl;
			continue;
		}
		string A = toString(a - 1);
		string B = toString(b);
		flag++;
		ll x = calc(0, 0, 0, 0, A);
		flag++;
		ll y = calc(0, 0, 0, 0, B);
		cout << "Case " << cases++ << ": " << y - x << endl;
	}
	return 0;
}