bool isPalindrome[100][100];
// Find the palindromes of a string in O(n^2)

int main()
{
	ios_base::sync_with_stdio(0);
	// freopen("in.txt","r",stdin);

	string s;

	cin>>s;

	int len=s.size();

	for(int i=0; i<len; i++)
		isPalindrome[i][i]=true;

	for(int k=1; k<len; k++)
	{
		for(int i=0; i+k<len; i++)
		{
			int j=i+k;

			isPalindrome[i][j]=(s[i]==s[j]) && 
			(isPalindrome[i+1][j-1] || i+1>=j-1);
		}
	}

	return 0;
}




