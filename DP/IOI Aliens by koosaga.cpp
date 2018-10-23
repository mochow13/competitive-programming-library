#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

vector<pi> v;
pi dp[MAXN];

struct point{
	lint first;
	lint second;
	int cnt;
};

struct cht{
	vector<point> v;
	void clear(){ v.clear(); }
	long double cross(point a, point b){
		return ((long double)(b.second - a.second) / (b.first - a.first));
	}
	void add_line(int x, lint y, int z){
		while(v.size() >= 2 && cross(v[v.size()-2], v.back()) > cross(v.back(), (point){x, y, z})){
			v.pop_back();
		}
		v.push_back({x, y, z});
	}
	pi query(int x){
		int s = 0, e = v.size()-1;
		auto f = [&](int p){
		return v[p].first * x + v[p].second;
		};
		while(s != e){
			int m = (s+e)/2;
			if(f(m) <= f(m+1)) e = m;
			else s = m+1;
		}
		return pi(v[s].first * x + v[s].second, v[s].cnt);
	}
}cht;

pi trial(lint l){
	cht.clear();
	for(int i=1; i<=v.size(); i++){
		cht.add_line(2 * 2 * v[i-1].first, dp[i-1].first + 
			2ll * v[i-1].first * v[i-1].first, dp[i-1].second);
		dp[i] = cht.query(-v[i-1].second);
		dp[i].first += 2ll * v[i-1].second * v[i-1].second + l; // l is penalty
		dp[i].second++;
		if(i != v.size()){
			lint c = max(0ll, v[i-1].second - v[i].first);
			dp[i].first -= 2 * c * c;
		}
	}
	return dp[v.size()];
}

long long take_photos(int n, int m, int k, std::vector<int> r, std::vector<int> c) {
	vector<pi> w;
	for(int i=0; i<n; i++){
		if(r[i] > c[i]) swap(r[i], c[i]);
		w.push_back({r[i]-1, c[i]});
	}
	sort(w.begin(), w.end(), [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	for(auto &i : w){
		if(v.empty() || v.back().second < i.second){
			v.push_back(i);
		}
	}
	lint s = 0, e = 2e12;
	while(s != e){
		lint m = (s+e)/2;
		// See how many groups are made with penalty 2*m+1
		if(trial(2 * m + 1).second <= k) e = m;
		else s = m+1;
	}
	return trial(s * 2).first / 2 - s * k;
}