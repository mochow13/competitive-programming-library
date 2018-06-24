int sideOf(const PT &s, const PT &e, const PT &p) 
{
	ll a = cross(e-s,p-s);
	return (a > 0) - (a < 0);
}

bool onSegment(const PT &s, const PT &e, const PT &p) 
{
	PT ds = p-s, de = p-e;
	return cross(ds,de) == 0 && dot(ds,de) <= 0;
}

/* 
Main routine
Description: Determine whether a point t lies inside a given polygon (counter-clockwise order).
The polygon must be such that every point on the circumference is visible from the first point in the vector.
It returns 0 for points outside, 1 for points on the circumference, and 2 for points inside.
*/

int insideHull2(const vector<PT> &H, int L, int R, const PT &p) {
	int len = R - L;
	if (len == 2) {
		int sa = sideOf(H[0], H[L], p);
		int sb = sideOf(H[L], H[L+1], p);
		int sc = sideOf(H[L+1], H[0], p);
		if (sa < 0 || sb < 0 || sc < 0) return 0;
		if (sb==0 || (sa==0 && L == 1) || (sc == 0 && R == (int)H.size()))
			return 1;
		return 2;
	}
	int mid = L + len / 2;
	if (sideOf(H[0], H[mid], p) >= 0)
		return insideHull2(H, mid, R, p);
	return insideHull2(H, L, mid+1, p);
}

int insideHull(const vector<PT> &hull, const PT &p) {
	if ((int)hull.size() < 3) return onSegment(hull[0], hull.back(), p);
	else return insideHull2(hull, 1, (int)hull.size(), p);
}
