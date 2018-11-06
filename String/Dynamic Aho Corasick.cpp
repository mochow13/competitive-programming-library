#include <bits/stdtr1c++.h>

#define LOG 19
#define LET 26
#define MAX 300010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct aho_corasick{
    int id, edge[256];
    vector <long long> counter;
    vector <string> dictionary;
    vector <map<char, int> > trie;
    vector <int> leaf, fail, dp[LET];

    inline int node(){
        leaf.push_back(0);
        counter.push_back(0);
		trie.push_back(map<char, int>());
		return id++;
    }

    inline int size(){
        return dictionary.size();
    }

    void clear(){
        trie.clear();
        dictionary.clear();
        fail.clear(), leaf.clear(), counter.clear();
        for (int i = 0; i < LET; i++) dp[i].clear();

        id = 0, node();
        for (int i = 'a'; i <= 'z'; i++) edge[i] = i - 'a'; /// change here if different character set
    }

    aho_corasick(){
        clear();
    }

    inline void insert(const char* str){
        int j, x, cur = 0;
        for (j = 0; str[j] != 0; j++){
            x = edge[str[j]];
            if (!trie[cur].count(x)){
                int next_node = node();
                trie[cur][x] = next_node;
            }
            cur = trie[cur][x];
        }

        leaf[cur]++;
        dictionary.push_back(str);
    }

    inline void build(){ /// remember to call build
        vector <pair<int, pair<int, int> > > Q;
        fail.resize(id, 0);
        Q.push_back({0, {0, 0}});

        for (int i = 0; i < LET; i++) dp[i].resize(id, 0);
        for (int i = 0; i < id; i++){
            for (int j = 0; j < LET; j++){
                dp[j][i] = i;
            }
        }

        for(int i = 0; i < Q.size(); i++){
            int u = Q[i].first;
            int p = Q[i].second.first;
            char c = Q[i].second.second;
            for(auto& it: trie[u]) Q.push_back({it.second, {u, it.first}});

            if (u){
                int f = fail[p];
                while (f && !trie[f].count(c)) f = fail[f];
                if(!trie[f].count(c) || trie[f][c] == u) fail[u] = 0;
                else fail[u] = trie[f][c];
                counter[u] = leaf[u] + counter[fail[u]];

                for (int j = 0; j < LET; j++){
                    if (u && !trie[u].count(j)) dp[j][u] = dp[j][fail[u]];
                }
            }
        }
    }

    inline int next(int cur, char ch){
        int x = edge[ch];
        cur = dp[x][cur];
        if (trie[cur].count(x)) cur = trie[cur][x];
        return cur;
    }

    long long count(const char* str){ /// total number of occurrences of all words from dictionary in str
        int cur = 0;
        long long res = 0;

        for (int j = 0; str[j] && id > 1; j++){ /// id > 1 because build will not be called if empty dictionary in dynamic aho corasick
            cur = next(cur, str[j]);
            res += counter[cur];
        }
        return res;
    }
};

struct dynamic_aho{ /// dynamic aho corasick in N log N
    aho_corasick ar[LOG];

    dynamic_aho(){
        for (int i = 0; i < LOG; i++) ar[i].clear();
    }

    inline void insert(const char* str){
        int i, k = 0;
        for (k = 0; k < LOG && ar[k].size(); k++){}

        ar[k].insert(str);
        for (i = 0; i < k; i++){
            for (auto s: ar[i].dictionary){
                ar[k].insert(s.c_str());
            }
            ar[i].clear();
        }
        ar[k].build();
    }

    long long count(const char* str){
        long long res = 0;
        for (int i = 0; i < LOG; i++) res += ar[i].count(str);
        return res;
    }
};

char str[MAX];

int main(){
    dynamic_aho ar[2];
    int t, i, j, k, l, flag;

    scanf("%d", &t);
    while (t--){
        scanf("%d %s", &flag, str);
        if (flag == 3){
            printf("%lld\n", ar[0].count(str) - ar[1].count(str));
            fflush(stdout);
        }
        else ar[flag - 1].insert(str);
    }
    return 0;
}
