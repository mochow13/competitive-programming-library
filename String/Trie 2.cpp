const int MaxN = 100005;
int sz;

int nxt[MaxN][55];
int en[MaxN];

bool isSmall(char ch)
{
	return ch>='a' && ch<='z';
}

int getId(char ch)
{
	if(isSmall(ch)) return ch-'a';
	else return ch-'A'+26;
}

void insert (char *s, int l) 
{
	int v = 0;

	for (int i = 0; i < l; ++i) {

		int c=getId(s[i]);

		if (nxt[v][c]==-1) 
		{
			ms(nxt[sz],-1);
			nxt[v][c]=sz++;
			en[sz]=0;
			// created[sz] = true;
		}

		v = nxt[v][c];
	}
	++en[v];
}

int search (char *tmp, int l) {

	int v = 0;
	
	for (int i = 0; i < l; ++i) {

		int c=getId(tmp[i]);

		if (nxt[v][c]==-1)
			return 0;

		v = nxt[v][c];
	}
	return en[v];
}

void init()
{
	sz=1;
	en[0]=0;
	ms(nxt[0],-1);
}