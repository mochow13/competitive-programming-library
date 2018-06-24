// How many values in a range are less than or equal to the given value?
// The key idea is to sort the values under a node in the segment tree and use binary search to find
// the required count
// Complexity is O(nlog^2n) for building
// The actual problem needed the number of such values and the cumulative sum of them
// Tree[node].All has all the values and Tree[node].Pref has the prefix sums
// Remember: upper_bound gives the number of values less than or equal to given value in a sorted range
struct info
{
	vector<ll> All, Pref;
} Tree[MAX * 4];
ll T[MAX], Prefix[MAX];
void build(int node, int l, int r)
{
	if (l == r)
	{
		Tree[node].All.pb(T[l]);
		Tree[node].Pref.pb(T[l]);
		return;
	}
	int mid = (l + r) / 2;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	for (auto it : Tree[lc].All)
		Tree[node].All.pb(it);
	for (auto it : Tree[rc].All)
		Tree[node].All.pb(it);
	SORT(Tree[node].All);
	ll now = 0;
	for (auto it : Tree[node].All)
	{
		Tree[node].Pref.pb(now + it);
		now += it;
	}
}
pair<ll, ll> query(int node, int l, int r, int x, int y, int val)
{
	if (x > r || y < l) return MP(0LL, 0LL);
	if (x <= l && r <= y)
	{
		int idx = upper_bound(Tree[node].All.begin(), Tree[node].All.end(), val) - Tree[node].All.begin();
		if (idx > 0) return MP(Tree[node].Pref[idx - 1], idx);
		return MP(0LL, 0LL);
	}
	int mid = (l + r) / 2;
	pair<ll, ll> ret, left, right;
	left = query(lc, l, mid, x, y, val);
	right = query(rc, mid + 1, r, x, y, val);
	ret.first += left.first; ret.second += left.second;
	ret.first += right.first; ret.second += right.second;
	return ret;
}