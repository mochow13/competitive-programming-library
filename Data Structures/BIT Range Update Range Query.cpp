class BITrangeOperations
{
public:

	ll Tree[MAX+7][2];

	void update(int idx, ll x, bool t)
	{
		while(idx<=MAX)
		{
			Tree[idx][t]+=x;
			idx+=(idx&-idx);
		}
	}
	
	ll query(int idx, bool t)
	{
		ll sum=0;
		while(idx>0)
		{
			sum+=Tree[idx][t];
			idx-=(idx&-idx);
		}
		return sum;
	}
	
	// Returns sum from [0,x]
	ll sum(int x)
	{
		return (query(x,0)*x)-query(x,1);
	}

	void updateRange(int l, int r, ll val)
	{
		update(l,val,0);
		update(r+1,-val,0);
		update(l,val*(l-1),1);
		update(r+1,-val*r,1);
	}

	ll rangeSum(int l, int r)
	{
		return sum(r)-sum(l-1);
	}
};