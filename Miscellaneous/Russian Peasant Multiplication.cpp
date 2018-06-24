// calculate (a*b)%m
// Particularly useful when a, b, m all are large like 1e18
ll RussianPeasantMultiplication(ll a, ll b, ll m)
{
	ll ret=0;

	while(b)
	{
		if(b&1)
		{
			ret+=a;
			if(ret>=m) ret-=m;
		}

		a=(a<<1);

		if(a>=m) a-=m;

		b>>=1;
	}

	return ret;
}