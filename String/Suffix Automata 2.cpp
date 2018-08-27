struct state {
    ll len, link;
    map<char,ll, less<char> >next; // use less for kth lexiograpical string evaluation
};

state st[MAX*2];
ll sz, last;

void sa_init() {
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].next.clear();
    ++sz;
}

ll cnt[MAX*2];

ll distSubtringCount;

void sa_extend (char c) {
    ll cur = sz++;
    st[cur].next.clear();
    cnt[cur] = 1;
    st[cur].len = st[last].len + 1;
    ll p;
    for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link){
        st[p].next[c] = cur;
    }
    if (p == -1){
        st[cur].link = 0;
    }
    else {
        ll q = st[p].next[c];
        if (st[p].len + 1 == st[q].len){
            st[cur].link = q;
        }
        else {
            ll clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            for (; p!=-1 && st[p].next[c]==q; p=st[p].link){
                st[p].next[c] = clone;
            }
            distSubtringCount-=st[q].len-st[st[q].link].len;
            st[q].link = st[cur].link = clone;
            distSubtringCount+=st[q].len-st[st[q].link].len;
            distSubtringCount+=st[clone].len-st[st[clone].link].len;
        }
    }
    last = cur;
    distSubtringCount+=st[cur].len-st[st[cur].link].len;
}

void calc_cnt(){
    vpl sorter;
    f(i,0,sz) sorter.pb(mp(st[i].len, i));
    sort(all(sorter));
    fd(i,sz-1,-1){
        ll k = sorter[i].second;
        cnt[st[k].link] += cnt[k];
    }
}


ll get_cnt(string s){
    ll now = 0;
    f(i,0,s.size()){
        if(!st[now].next.count(s[i])) return 0;
        now = st[now].next[s[i]];
    }
    return cnt[now];
}

ll first_occur(string s){
    ll now = 0;
    f(i,0,s.size()){
        if(!st[now].next.count(s[i])) return -1;
        now = st[now].next[s[i]];
    }
    return st[now].len - s.size();
}

string lcs (string s, string t) {
	sa_init();
	for (int i=0; i<(int)s.length(); ++i)
		sa_extend (s[i]);

	int v = 0,  l = 0,
		best = 0,  bestpos = 0;
	for (int i=0; i<(int)t.length(); ++i) {
		while (v && ! st[v].next.count(t[i])) {
			v = st[v].link;
			l = st[v].len;
		}
		if (st[v].next.count(t[i])) {
			v = st[v].next[t[i]];
			++l;
		}
		if (l > best)
			best = l,  bestpos = i;
	}
	return t.substr (bestpos-best+1, best);
}
// Kth Lexiographicaly smallest string
ll dp[MAX];   // dp[i] = number of different substring starting from i

ll F(ll u){
    if(dp[u] != -1) return dp[u];
    dp[u] = 1;
    for(map <char, ll> :: iterator it = st[u].next.begin(); it != st[u].next.end(); it++){
        dp[u] += F(it->second);
    }
    return dp[u];
}

string klex(ll u, ll k){
    if(!k) return "";
    for(map <char, ll> :: iterator it = st[u].next.begin(); it != st[u].next.end(); it++){
        ll num = F(it->second);
        if(num < k) k -= num;
        else{
            string ret;
            ret.pb(it->first);
            ret = ret + klex(it->second, k-1);
            return ret;
        }
    }
}

ll min_cyclic_shift(string s){
    sa_init();
    f(i,0,s.size()) sa_extend(s[i]);
    f(i,0,s.size()) sa_extend(s[i]);
    ll now = 0;
    f(i,0,s.size()) now = st[now].next.begin()->second;
    return st[now].len - s.size();
}

char s[MAX];

int main(){
    string s;
    cin >> s;
    cout << min_cyclic_shift(s) << endl;
}


