struct Node
{
	int cntL, cntR, lIdx, rIdx;
	Node()
	{
		cntL = cntR = 0;
		lIdx = rIdx = -1;
	}
};
Node Tree[MAX];
int globalIdx = 0;
class Trie
{
public:
	void insert(int val, int idx, int depth)
	{
		for (int i = depth - 1; i >= 0; i--)
		{
			bool bit = val & (1 << i);
			// cout<<"bit now: "<<bit<<endl;
			if (bit)
			{
				Tree[idx].cntR++;
				if (Tree[idx].rIdx == -1)
				{
					Tree[idx].rIdx = ++globalIdx;
					idx = globalIdx;
				}
				else idx = Tree[idx].rIdx;
			}
			else
			{
				Tree[idx].cntL++;
				if (Tree[idx].lIdx == -1)
				{
					Tree[idx].lIdx = ++globalIdx;
					idx = globalIdx;
				}
				else idx = Tree[idx].lIdx;
			}
		}
	}
	int query(int val, int compVal, int idx, int depth)
	{
		int ans = 0;
		for (int i = depth - 1; i >= 0; i--)
		{
			bool valBit = val & (1 << i);
			bool compBit = compVal & (1 << i);
			if (compBit)
			{
				if (valBit)
				{
					ans += Tree[idx].cntR;
					idx = Tree[idx].lIdx;
				}
				else
				{
					ans += Tree[idx].cntL;
					idx = Tree[idx].rIdx;
				}
			}
			else
			{
				if (valBit)
				{
					idx = Tree[idx].rIdx;
				}
				else
				{
					idx = Tree[idx].lIdx;
				}
			}
			if (idx == -1) break;
		}
		return ans;
	}
	void clear()
	{
		for (int i = 0; i <= globalIdx; i++)
		{
			Tree[i].cntL = 0;
			Tree[i].cntR = 0;
			Tree[i].rIdx = -1;
			Tree[i].lIdx = -1;
		}
		globalIdx = 0;
	}
};
int main()
{
	// ios_base::sync_with_stdio(0);
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("in.txt","r",stdin);
	// Given an array of positive integers you have to print the number of
	// subarrays whose XOR is less than K.
	int test, n, k, x;
	Trie T;
	scanf("%d", &test);
	while (test--)
	{
		scanf("%d%d", &n, &k);
		T.insert(0, 0, 20);
		int pre = 0;
		ll ans = 0;
		FOR(i, 0, n)
		{
			scanf("%d", &x);
			pre ^= x;
			// prnt(pre);
			ans += T.query(pre, k, 0, 20);
			T.insert(pre, 0, 20);
		}
		printf("%lld\n", ans);
		T.clear();
	}
	return 0;
}