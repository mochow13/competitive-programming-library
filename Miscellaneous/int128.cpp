__int128 input(){
    string s;
    cin >> s;
    ll fst = (s[0] == '-') ? 1 : 0;
    __int128 v = 0;
    f(i,fst,s.size()) v = v * 10 + s[i] - '0';
    if(fst) v = -v;
    return v;
}

ostream& operator << (ostream& os,const __int128& v) {
    string ret, sgn;
    __int128 n = v;
    if(v < 0) sgn = "-", n = -v;
    while(n) ret.pb(n % 10 + '0'), n /= 10;
    reverse(all(ret));
    ret = sgn + ret;
    os << ret;
    return os;
}

int main(){
    __int128 n = input();
    cout << n << endl;
}

