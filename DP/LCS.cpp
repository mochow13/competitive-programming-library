string a, b;
int dp[100][100];
string l;
void printLcs(int i, int j)
{
	if (a[i] == '\0' || b[j] == '\0')
	{
		cout << l << endl;
		return;
	}
	if (a[i] == b[j])
	{
		l += a[i];
		printLcs(i + 1, j + 1);
	}
	else
	{
		if (dp[i + 1][j] > dp[i][j + 1])
			printLcs(i + 1, j);
		else
			printLcs(i, j + 1);
	}
}
void printAll(int i, int j)
{
	if (a[i] == '\0' || b[j] == '\0')
	{
		prnt(l);
		return;
	}
	if (a[i] == b[j])
	{
		l += a[i];
		printAll(i + 1, j + 1);
		l.erase(l.end() - 1);
	}
	else
	{
		if (dp[i + 1][j] > dp[i][j + 1])
			printAll(i + 1, j);
		else if (dp[i + 1][j] < dp[i][j + 1])
			printAll(i, j + 1);
		else
		{
			printAll(i + 1, j);
			printAll(i, j + 1);
		}
	}
}
int lcslen (int i, int j)
{
	if (a[i] == '\0' || b[j] == '\0')
		return 0;
	if (dp[i][j] != -1)
		return dp[i][j];
	int ans = 0;
	if (a[i] == b[j])
	{
		ans = 1 + lcslen(i + 1, j + 1);
	}
	else
	{
		int x = lcslen(i, j + 1);
		int y = lcslen(i + 1, j);
		ans = max(x, y);
	}
	return dp[i][j] = ans;
}

int main()
{
	cin >> a >> b;
	ms(dp, -1);
	cout << lcslen(0, 0) << endl;
	printLcs(0, 0);
	l.clear();
	printAll(0, 0);
	return 0;
}