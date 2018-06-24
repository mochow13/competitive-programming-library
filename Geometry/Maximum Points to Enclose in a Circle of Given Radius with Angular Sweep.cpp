typedef pair<double,bool> pdb;

#define START 0
#define END 1

struct PT 
{
	double x, y; 
	PT() {}
	PT(double x, double y) : x(x), y(y) {}
	PT(const PT &p) : x(p.x), y(p.y)    {}
	PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
	PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
	PT operator * (double c)     const { return PT(x*c,   y*c  ); }
	PT operator / (double c)     const { return PT(x/c,   y/c  ); }
};

PT p[505];
double dist[505][505];
int n, m;

void calcDist()
{
	FOR(i,0,n)
	{
		FOR(j,i+1,n)
			dist[i][j]=dist[j][i]=sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)
				+(p[i].y-p[j].y)*(p[i].y-p[j].y));
	}
}

// Returns maximum number of points enclosed by a circle of radius 'radius'
// where the circle is pivoted on point 'point' 
// 'point' is on the circumfurence of the circle

int intelInside(int point, double radius)
{
	vector<pdb> ranges;

	FOR(j,0,n)
	{
		if(j==point || dist[j][point]>2*radius) continue;

		double a1=atan2(p[point].y-p[j].y,p[point].x-p[j].x);
		double a2=acos(dist[point][j]/(2*radius));

		ranges.pb({a1-a2,START});
		ranges.pb({a1+a2,END});
	}

	sort(ALL(ranges));

	int cnt=1, ret=cnt;

	for(auto it: ranges)
	{
		if(it.second) cnt--;
		else cnt++;
		ret=max(ret,cnt);
	}

	return ret;
}

// returns maximum amount of points enclosed by the circle of radius r
// Complexity: O(n^2*log(n))

int go(double r) 
{
	int cnt=0;

	FOR(i,0,n)
	{
		cnt=max(cnt,intelInside(i,r));
	}

	return cnt;
}