struct Matrix
{
	ll mat[MAX][MAX];
	Matrix(){}
	// This initialization is important.
	// Input matrix should be initialized separately
	void init(int sz)
	{
		ms(mat,0);
		for(int i=0; i<sz; i++) mat[i][i]=1;
	}
} aux;

void matMult(Matrix &m, Matrix &m1, Matrix &m2, int sz)
{
	ms(m.mat,0);
	// This only works for square matrix	
	FOR(i,0,sz)
	{
		FOR(j,0,sz)
		{
			FOR(k,0,sz)
			{
				m.mat[i][k]=(m.mat[i][k]+m1.mat[i][j]*m2.mat[j][k])%mod;
			}
		}
	}
	/* We can also do this if MOD*MOD fits long long
	long long MOD2 = MOD * MOD;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			long long tmp = 0;
				for(int k = 0; k < n; k++) {
				// Since A and B are taken modulo MOD, the product A[i][k] * B[k][j] is
				// not more than MOD * MOD.
				tmp += A[i][k] * 1ll * B[k][j];
				while(tmp >= MOD2) // Taking modulo MOD2 is easy, because we can do it by subtraction
				tmp -= MOD2;
			}
		result[i][j] = tmp % MOD; // One % operation per resulting element
		}
	*/
}

Matrix expo(Matrix &M, int n, int sz)
{
	Matrix ret;
	ret.init(sz);

	if(n==0) return ret;
	if(n==1) return M;

	Matrix P=M;

	while(n!=0)
	{
		if(n&1)
		{
			aux=ret;
			matMult(ret,aux,P,sz);
		}

		n>>=1;

		aux=P; matMult(P,aux,aux,sz);
	}

	return ret;
}
