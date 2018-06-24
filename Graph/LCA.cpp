vi graph[100];
int P[100], L[100], table[100][20];

void dfs(int from, int to, int depth)
{
	P[to]=from;
	L[to]=depth;
	FOR(i,0,(int)graph[to].size())
	{
		int v=graph[to][i];
		if(v==from)
			continue;
		dfs(to,v,depth+1);
	}
}

int query(int n, int p, int q)
{
	if(L[p]<L[q]) swap(p,q);
	
	int x=1;
	
	while(true)
	{
		if((1<<(x+1))>L[p])
			break;
		x++;
	}
	
	FORr(i,x,0)
	{
		if(L[p]-(1<<i) >= L[q])
			p=table[p][i];
	}
	
	if(p==q) return p;
	
	FORr(i,x,0)
	{
		if(table[p][i]!=-1 && table[p][i]!=table[q][i])
		{
			p=table[p][i];
			q=table[q][i];
		}
	}
	
	return P[p];
}


void build(int n)
{
	ms(table,-1);
	
	FOR(i,0,n)
		table[i][0]=P[i];
	
	for(int j=1; 1<<j < n; j++)
	{
		for(int i=0; i<n; i++)
		{	
			if(table[i][j-1]!=-1)
				table[i][j]=table[table[i][j-1]][j-1];
		}
	}
}
		
		
		
		
		
		
		
		
		
