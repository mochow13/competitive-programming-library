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
				m.mat[i][k]=(m.mat[i][k]+m1.mat
					[i][j]*m2.mat[j][k])%mod;
			}
		}
	}
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
