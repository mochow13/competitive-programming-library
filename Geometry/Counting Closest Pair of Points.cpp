int n;
struct Points
{
	double x, y;
	Points() {}
	Points(double x, double y) : x(x), y(y) { }
	bool operator<(const Points &a) const
	{
		return x < a.x;
	}
};
bool comp1(const Points &a, const Points &b)
{
	return a.x < b.x;
}
bool comp2(const Points &a, const Points &b)
{
	return a.y < b.y;
}
void printPoint(Points a)
{
	cout << a.x << " " << a.y << endl;
}
Points P[10005];
typedef set<Points, bool(*)(const Points&, const Points&)> setType;
typedef setType::iterator setIT;
setType s(&comp2);
double euclideanDistance(const Points &a, const Points &b)
{
// prnt((double)(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
map<double, map<double, int> > CNT;
int main()
{
// ios_base::sync_with_stdio(0);
// cin.tie(NULL); cout.tie(NULL);
// freopen("in.txt","r",stdin);
	while ((cin >> n) && n)
	{
		FOR(i, 0, n) cin >> P[i].x >> P[i].y;
		sort(P, P + n, comp1);
		FOR(i, 0, n)
		{
// printPoint(P[i]);
			s.insert(P[i]);
			CNT[P[i].x][P[i].y]++;
		}
// To check repeated points :/
// for(auto it: s) printPoint(it);
		double ans = 10000;
		int idx = 0;
		FOR(j, 0, n)
		{
// cout<<"Point now: "; printPoint(P[j]);
			if (CNT[P[j].x][P[j].y] > 1) ans = 0;
			Points it = P[j];
			while (it.x - P[idx].x > ans)
			{
				s.erase(P[idx]);
				idx++;
			}
			Points low = Points(it.x, it.y - ans);
			Points high = Points(it.x, it.y + ans);
			setIT lowest = s.lower_bound(low);
			if (lowest != s.end())
			{
				setIT highest = s.upper_bound(high);
				for (setIT now = lowest; now != highest; now++)
				{
					double cur = sqrt(euclideanDistance
					                  (*now, it));
// prnt(cur);
					if (cur == 0) continue;
// cout<<"Here:"<<endl;
// printPoint(*now); printPoint(it); prnt
					(cur);
					if (cur < ans)
					{
						ans = cur;
					}
				}
			}
			s.insert(it);
		}
// cout<<"Set now:"<<endl;
// for(auto I: s) printPoint(I);
		if (ans < 10000) cout << setprecision(4) << fixed << ans << endl;
		else prnt("INFINITY");
		s.clear();
		CNT.clear();
	}
	return 0;
}