struct cht
{
	vector<pii> hull;
	vector<int> id;
	
	int cur=0;
	
	cht()
	{
		hull.clear();
		id.clear();
	}

	// Might need double here

	bool useless(const pii left, const pii middle, const pii right)
	{
		return 
		1LL*(middle.second-left.second)*(middle.first-right.first)
		>=1LL*(right.second-middle.second)*(left.first-middle.first);
	}

	// Inserting line a*x+b with index idx
	// Before inserting one by one, all the lines are sorted by slope

	void insert(int idx, int a, int b)
	{
		if(hull.empty())
		{
			hull.pb(MP(a, b));
			id.pb(idx);
		}
		else
		{
			if(hull.back().first==a)
			{
				if(hull.back().second>=b)
				{
					return;
				}
				else
				{
					hull.pop_back();
					id.pop_back();
				}
			}
			while(hull.size()>=2 && useless(hull[hull.size()-2], hull.back(), MP(a, b)))
			{
				hull.pop_back();
				id.pop_back();
			}
			hull.pb(MP(a,b));
			id.pb(idx);
		}
	}

	// returns maximum value and the index of the line
	// Pointer approach: the queries are sorted non-decreasing
	// Otherwise, we will need binary search

	pair<ll,int> query(int x)
	{
		ll ret=-INF;
		int idx=-1;
		for(int i=cur ; i < hull.size() ; i++)
		{
			ll tmp=1LL*hull[i].first*x + hull[i].second;

			if(tmp>ret)
			{
				ret=tmp;
				cur=i;
				idx=id[i];
			}
			else
			{
				break;
			}
		}
		return {ret,idx};
	}
};


// Slope decreasing, query minimum - Query point increasing.
// Slope increasing, query maximum - Query point increasing.
// Slope decreasing, query maximum - Query point decreasing.
// Slope increasing, query minimum - Query point decreasing.
