/* Problem: Given a bipartite graph, find out minimum number of colors
to color all the edges such that no two adjacent edges have a same color
assigned. Number of minimum colors equals the max degree of a vertex in 
the bipartite graph. We also need to assign colors to each edge.
*/ 

/* Comment by 300iq:
Minimum answer is max degree.
If max degree  ≤  1, we can just color all edges in one color.
Else, let's split edges of the graph into two sets, such that max degree 
will be  ≤  (max degree + 1) / 2 in each of these two sets. You can do it 
with euler circuit, add some dummy vertex to the left and right part, and 
connect with them vertices with odd degree (and maybe you need to connect 
them if they have odd degree). And then color the edges into two colors by 
order of euler circuit. Then separate all inital edges into two groups by the 
color. Then let's solve recursively for these two sets, and then just merge the answers.
*/

struct edge
{
    int a, b;
};

const int N = 1e6 + 7;
vector <int> g[N];
int col[N];
vector <edge> glob_edges;
bool vis[N];
bool us[N];
int pp;

void dfs(int v)
{
    us[v] = true;
    while (g[v].size() > 0)
    {
        int ind = g[v].back();
        g[v].pop_back();
        if (vis[ind])
        {
            continue;
        }
        vis[ind] = true;
        col[ind] = (pp ^= 1);
        dfs(glob_edges[ind].a == v ? glob_edges[ind].b : glob_edges[ind].a);
    }
}

vector <int> solve(vector <edge> e)
{
    if (e.empty())
    {
        return {};
    }
    vector <int> l, r;
    for (auto c : e)
    {
        l.push_back(c.a);
        r.push_back(c.b);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    l.resize(unique(l.begin(), l.end()) - l.begin());
    r.resize(unique(r.begin(), r.end()) - r.begin());
    glob_edges.clear();
    int x = (int) l.size() + 1, y = (int) r.size() + 1;
    for (int i = 0; i < x + y; i++) g[i].clear();
    int ind = 0;
    for (auto &c : e)
    {
        c.a = lower_bound(l.begin(), l.end(), c.a) - l.begin();
        c.b = lower_bound(r.begin(), r.end(), c.b) - r.begin();
        auto ret = c;
        ret.b += x;
        glob_edges.push_back(ret);
        g[ret.a].push_back(ind);
        g[ret.b].push_back(ind);
        ind++;
    }
    vector <int> ids;
    int mx = 0;
    for (int i = 0; i < x + y; i++)
    {
        us[i] = 0;
        mx = max(mx, (int) g[i].size());
        if (g[i].size() % 2)
        {
            ids.push_back(i);
        }
    }
    bool bad = false;
    for (int i = 0; i < x + y; i++)
    {
        if (g[i].size() > 1)
        {
            bad = true;
        }
    }
    if (!bad)
    {
        vector <int> res(ind);
        return res;
    }
    else
    {
        vector <int> deg(x + y);
        for (int v : ids)
        {
            if (v < x)
            {
                glob_edges.push_back({v, x + y - 1});
                g[v].push_back(ind);
                g[x + y - 1].push_back(ind);
                ind++;
            }
            else
            {
                glob_edges.push_back({v, x - 1});
                g[v].push_back(ind);
                g[x - 1].push_back(ind);
                ind++;
            }
        }
        if (g[x - 1].size() % 2)
        {
            glob_edges.push_back({x - 1, x + y - 1});
            g[x - 1].push_back(ind);
            g[x + y - 1].push_back(ind);
            ind++;
        }
        for (int i = 0; i < ind; i++)
        {
            col[i] = -1;
        }
        for (int i = 0; i < ind; i++)
        {
            vis[i] = 0;
        }
        for (int i = 0; i < x + y; i++)
        {
            if (!g[i].empty())
            {
                dfs(i);
            }
        }
        vector <edge> to_l, to_r;
        vector <int> cols;
        for (int i = 0; i < (int) e.size(); i++)
        {
            cols.push_back(col[i]);
            if (col[i] == 0)
            {
                to_l.push_back(e[i]);
            }
            else
            {
                to_r.push_back(e[i]);
            }
        }
        auto x = solve(to_l);
        auto y = solve(to_r);
        int mx = *max_element(x.begin(), x.end()) + 1;
        int p_x = 0, p_y = 0;
        vector <int> ans;
        for (int i = 0; i < (int) e.size(); i++)
        {
            if (cols[i] == 0)
            {
                ans.push_back(x[p_x++]);
            }
            else
            {
                ans.push_back(mx + y[p_y++]);
            }
        }
        return ans;
    }
}
int main()
{
    vector <edge> e;
    int l, r, m;
    cin >> l >> r >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        e.push_back({a, b});
    }
    auto ret = solve(e);
    cout << *max_element(ret.begin(), ret.end()) + 1 << '\n';
    for (int c : ret)
    {
        cout << c + 1 << '\n';
    }
}