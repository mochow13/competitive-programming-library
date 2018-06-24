const int MAXN = (1 << 20);
const int MAXLOG = 64;

struct basis
{
    int64_t base[MAXLOG];

    void clear()
    {
		for(int i = MAXLOG - 1; i >= 0; i--)
			base[i] = 0;
    }

    void add(int64_t val)
    {
    	for(int i = MAXLOG - 1; i >= 0; i--)
			if((val >> i) & 1)
			{
				if(!base[i]) { base[i] = val; return; }
				else val ^= base[i];
			}
	}

    inline int size()
    {
    	int sz = 0;
    	for(int i = 0; i < MAXLOG; i++)
			sz += (bool)(base[i]);
		return sz;
    }

    int64_t max_xor()
    {
		int64_t res = 0;
		for(int i = MAXLOG - 1; i >= 0; i--)
			if(!((res >> i) & 1) && base[i])
				res ^= base[i];

		return res;
	}

    bool can_create(int64_t val)
    {
		for(int i = MAXLOG - 1; i >= 0; i--)
			if(((val >> i) & 1) && base[i])
				val ^= base[i];

		return (val == 0);
    }
};