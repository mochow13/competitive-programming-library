/* Problem: We have three types of queries: add a string to our dictionary,
delete an existing string from our dictionary, and for the given string s find 
the number of occurrences of the strings from the dictionary. If some string p 
from dictionary has several occurrences in s, we should count all of them.

Solution: If we have N strings in the dictionary, maintain log(N) Aho Corasick
automata. The i-th automata contains the first 2^k strings not included in the
previous automata. For example, if we have N = 19, we need 3 automata: {s[1]...s[16]},
{s[17]...s[18]}, and {s[19]}. To answer the query, we can traverse the logN automata
using the given query string.

To handle addition, first construct an automata using the single string, and then
while there are two automatons with the same number of strings, we merge them by 
constructing a new automaton using brute force. 
Complexity becomes O(total_length_of_all_string*log(number_of_insert_operations)).

To handle deletion, we just insert with a value -1 to store in endpoints of each
added string.
*/
const int N = 3e5+7; // maximum number of nodes
const int ALPHA = 26; // alphabate size
int node[20][N][ALPHA]; // stores nodes for id-th automaton
struct ahoCorasick
{
    int root, nnode;
    int link[N], cnt[N], id;
    bool dead;
    
    void init(int idx)
    {
    	dead = false; id = idx; root = 0; nnode = 0;
        ms(node[id][root],0);
        FOR(i,0,nnode+1) cnt[i] = 0;
    }
    void clear()
    {
    	dead = true;
    }
    // insert a word in automaton number 'id'.
    void insertword(string &s, int val)
    {
        int len = s.size();
        int now = root;

        FOR(i,0,len)
        {
            int nxt = s[i]-'a';

            if(!node[id][now][nxt])
            {
                node[id][now][nxt] = ++nnode;
                ms(node[id][nnode],0);
                cnt[nnode]=0;
            }
            now=node[id][now][nxt];
        }
        cnt[now]+=val;
        // an occurrence of a string happened in 'now'
        // if val=-1, it means an occurrence is removed
    }
    void insertdict(vector<string> &dict, vector<int> &vals)
    {
        // dict is the dictionary for current automaton
        // and vals can be 1 or -1 denoting addition or deletion of corresponding string
    	FOR(i,0,dict.size()) insertword(dict[i],vals[i]);
    }
    void pushLinks()
    {
        queue<int> Q; link[root]=-1;
        Q.push(root);
        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();

            for(int i=0; i<ALPHA; i++)
            {
                if(!node[id][u][i]) continue;
                int v = node[id][u][i];
                int l = link[u];

                while(l!=-1 && !node[id][l][i]) l = link[l];
                if(l!=-1) link[v] = node[id][l][i];
                else link[v] = 0;
                cnt[v]+=cnt[link[v]];
                Q.push(v);
            }
        }
    }
    // Returns how many occurrences of dictionary are there in query string p
    int query(string &p)
    {
        int u = root, ret = 0;
        for(char ch: p)
        {
            int nxt = ch-'a';
            while(u!=-1 && !node[id][u][nxt]) u = link[u];
            if(u==-1) u = 0;
            else u = node[id][u][nxt];
            ret+=cnt[u];
        }
        return ret;
    }
} aho[20];

vector<string> dict[20];
vector<int> vals[20];
// handles addition and deletion dynamically
void add(string &s, int val)
{
	dict[0].pb(s);
	vals[0].pb(val);
	for(int i=0; i<20; i++)
	{
		if(dict[i].size()>(1<<i)) // merging two automata
		{
			for(auto it: dict[i]) dict[i+1].pb(it);
			for(auto it: vals[i]) vals[i+1].pb(it);
			dict[i].clear();
			vals[i].clear();
			aho[i].clear(); // i-th automata is not relevant anymore
		}
		else
		{
			aho[i].init(i);
			aho[i].insertdict(dict[i],vals[i]);
			aho[i].pushLinks();
			break;
		}
	}
}

int n, t;
char in[N];
void Test()
{
	ahoCorasick aho;
	aho.init(0);
	string s = "o"; aho.insertword(s,1);
	s = "m"; aho.insertword(s,1);
	s = "h"; aho.insertword(s,1);
	aho.pushLinks();
	s = "moohh";
	prnt(aho.query(s));
}
int main()
{
    // Test();
    FOR(i,0,20) aho[i].clear(); 
    scanf("%d", &n);
    while(n--)
    {
    	scanf("%d%s", &t, in);
		string x = in;
    	if(t==1) add(x,1);
    	else if(t==2) add(x,-1)
    	else
    	{
    		ll ans = 0;
    		FOR(i,0,20) if(!aho[i].dead) ans+=aho[i].query(x);
    		printf("%lld\n", ans);
    		fflush(stdout); // needed because the problem forced online solution
    	}
    }
    return 0;
}