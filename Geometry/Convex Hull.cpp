struct PT
{
	int x, y;
	PT(){}
	PT(int x, int y) : x(x), y(y) {}
	bool operator < (const PT &P) const
	{
		return x<P.x || (x==P.x && y<P.y);
	}
};



ll cross(const PT p, const PT q, const PT r)   
{ 
	return (ll)(q.x-p.x)*(ll)(r.y-p.y)-(ll)(q.y-p.y)*(ll)(r.x-p.x);
}

vector<PT> Points, Hull;

void findConvexHull()
{
	int n=Points.size(), k=0;

	SORT(Points);

	// Build lower hull

	FOR(i,0,n)
	{
		while(Hull.size()>=2 && cross(Hull[Hull.size()-2],Hull.back(),Points[i])<=0)
		{
			Hull.pop_back();
			k--;
		}
		Hull.pb(Points[i]);
		k++;
	}

	// Build upper hull

	for(int i=n-2, t=k+1; i>=0; i--)
	{
		while(Hull.size()>=t && cross(Hull[Hull.size()-2],Hull.back(),Points[i])<=0)
		{
			Hull.pop_back();
			k--;
		}
		Hull.pb(Points[i]);
		k++;
	}

	Hull.resize(k);
}