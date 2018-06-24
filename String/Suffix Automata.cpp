// Counts number of distinct substrings

struct suffix_automaton
{
    map<char, int> to[MAX];
    int len[MAX], link[MAX];
    int last, psz = 0;

    void add_letter(char c)
    {
        int p = last, cl, q;
        if(to[p].count(c))
        {
            q = to[p][c];
            if(len[q] == len[p] + 1)
            {
                last = q;
                return;
            }

            cl = psz++;
            len[cl] = len[p] + 1;
            to[cl] = to[q];
            link[cl] = link[q];
            link[q] = cl;
            last = cl;

            for(; to[p][c] == q; p = link[p])
                to[p][c] = cl;

            return;
        }

        last = psz++;
        len[last] = len[p] + 1;

        for(; to[p][c] == 0; p = link[p])
            to[p][c] = last;

        if(to[p][c] == last)
        {
            link[last] = p;
            return;
        }

        q = to[p][c];
        if(len[q] == len[p] + 1)
        {
            link[last] = q;
            return;
        }

        cl = psz++;
        len[cl] = len[p] + 1;
        to[cl] = to[q];
        link[cl] = link[q];
        link[q] = cl;
        link[last] = cl;

        for(; to[p][c] == q; p = link[p])
            to[p][c] = cl;
    }

    void clear()
    {
        for(int i = 0; i < psz; i++)
            len[i] = 0, link[i] = 0, to[i].clear();
        psz = 1;
        last = 0;
    }

    void init(string s)
    {
        clear();
        for(int i = 0; i < s.size(); i++)
            add_letter(s[i]);
    }

    suffix_automaton() {psz = 0; clear();}
};

string s;
suffix_automaton SA;
ll cnt[MAX];
vi endpos[MAX];

int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(NULL); cout.tie(NULL);
    // freopen("in.txt","r",stdin);

    int test, cases=1;

    cin>>s;

    SA.clear();
    FOR(i,0,s.size())
    	SA.add_letter(s[i]), cnt[SA.last]++;

    FOR(i,0,SA.psz)
    {
    	endpos[SA.len[i]].pb(i);
    }

    ll ans=0;

    FORr(i,SA.psz-1,1)
    {
    	for(auto it: endpos[i])
    	{
    		cnt[SA.link[it]]+=cnt[it];
    		ans+=(SA.len[it]-SA.len[SA.link[it]]); // distinct occurrences
            // cnt[it] has occurrence of substring ending at node it
    	}
    }

    // cnt[x] has occurrences of state x
    // To calculate occurrence of an input string, we visit the automata using the letters
    // of the input string and find the last_state where it finishes
    // The cnt[last_state] should be the occurrence of this string

    prnt(ans);

    return 0;
}