vi primes;
bool status[MAX+7];

// Finds all the primes upto MAX

void sieve()
{
	for(int i=4; i<=MAX; i+=2)
		status[i]=true;

	for(int i=3; i*i<=MAX; i++)
	{
		if(!status[i])
		{
			for(int j=i*i; j<=MAX; j+=i+i)
				status[j]=true;
		}
	}

	primes.pb(2);

	FOR(i,3,MAX) 
	{
		if(!status[i])
			primes.pb(i);
	}
}