int phi[MAX];
void phi()
{
	for (int i = 1; i < MAX; i++) phi[i] = i;
	for (int i = 2; i < MAX; i++)
	{
		if (phi[i] == i)
		{
			for (int j = i; j < MAX; j += i)
			{
				phi[j] /= i;
				phi[j] *= (i - 1);
			}
		}
	}
}