ll Tree[MAX];
// This is equivalent to calculating lower_bound on prefix sums array
// LOGN = log(N)
int bit_search(int v)
{
	int sum = 0;
	int pos = 0;
	
	for(int i=LOGN; i>=0; i--)
	{
		if(pos + (1 << i) < N and sum + Tree[pos + (1 << i)] < v)
		{
			sum += Tree[pos + (1 << i)];
			pos += (1 << i);
		}
	}
	// +1 because 'pos' will have position of largest value less than 'v'
	return pos + 1;
}

void update(int idx, ll x)
{
	// Let, n is the number of elements and our queries are
	// of the form query(n)-query(l-1), i.e range queries
	// Then, we should never put N or MAX in place of n here.
	while(idx<=n)
	{
		Tree[idx]+=x;
		idx+=(idx&-idx);
	}
}

ll query(int idx)
{
	ll sum=0;
	while(idx>0)
	{
		sum+=Tree[idx];
		idx-=(idx&-idx);
	}
	return sum;
}

int main()
{
	// For point update range query:
	// Point update: update(x,val);
	// Range query (a,b): query(b)-query(a-1);

	// For range update point query:
	// Range update (a,b): update(a,v); update(b+1,-v);
	// Point query: query(x);
	
	// Let's just consider only one update: Add v to [a, b] while the rest elements of the array is 0.
	// Now, consider sum(0, x) for all possible x, again three situation can arise:
	// 1. 0 ≤ x < a : which results in 0
	// 2. a ≤ x ≤ b : we get v * (x - (a-1))
	// 3. b < x < n : we get v * (b - (a-1))
	// This suggests that, if we can find v*x for any index x, then we can get the sum(0, x) by subtracting T from it, where:
	// 1. 0 ≤ x < : Sum should be 0, thus, T = 0
	// 2. a ≤ x ≤ : Sum should be v*x-v*(a-1), thus, T = v*(a-1)
	// 3. b < x < n : Sum should be 0, thus, T = -v*b + v*(a-1)
	// As, we can see, knowing T solves our problem, we can use another BIT to store this additive amount from which we can get:
	// 0 for x < a, v*(a-1) for x in [a..b], -v*b+v(a-1) for x > b.

	// Now we have two BITs.
	// To add v in range [a, b]: Update(a, v), Update(b+1, -v) in the first BIT and Update(a, v*(a-1)) and Update(b+1, -v*b) on the second BIT.
	// To get sum in range [0, x]: you simply do Query_BIT1(x)*x - Query_BIT2(x);
	// Now you know how to find range sum for [a, b]. Just find sum(b) - sum(a-1) using the formula stated above.
    return 0;
}