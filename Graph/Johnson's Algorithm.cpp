/// Johnson's algorithm for all pair shortest paths in sparse graphs
/// Complexity: O(N * M) + O(N * M * log(N))

const long long INF = (1LL << 60) - 666;

struct edge{
    int u, v;
    long long w;
    edge(){}
    edge(int u, int v, long long w) : u(u), v(v), w(w){}

    void print(){
        cout << "edge " << u << " " << v << " " << w << endl;
    }
};

bool bellman_ford(int n, int src, vector <struct edge> E, vector <long long>& dis){
    dis[src] = 0;
    for (int i = 0; i <= n; i++){
        int flag = 0;
        for (auto e: E){
            if ((dis[e.u] + e.w) < dis[e.v]){
                flag = 1;
                dis[e.v] = dis[e.u] + e.w;
            }
        }
        if (flag == 0) return true;
    }
    return false;
}

vector <long long> dijkstra(int n, int src, vector <struct edge> E, vector <long long> potential){
    set<pair<long long, int> > S;
    vector <long long> dis(n + 1, INF);
    vector <long long> temp(n + 1, INF);
    vector <pair<int, long long> > adj[n + 1];

    dis[src] = temp[src] = 0;
    S.insert(make_pair(temp[src], src));
    for (auto e: E){
        adj[e.u].push_back(make_pair(e.v, e.w));
    }

    while (!S.empty()){
        pair<long long, int> cur = *(S.begin());
        S.erase(cur);

        int u = cur.second;
        for (int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first;
            long long w = adj[u][i].second;

            if ((temp[u] + w) < temp[v]){
                S.erase(make_pair(temp[v], v));
                temp[v] = temp[u] + w;
                dis[v] = dis[u] + w;
                S.insert(make_pair(temp[v], v));
            }
        }
    }
    return dis;
}

void johnson(int n, long long ar[MAX][MAX], vector <struct edge> E){
    vector <long long> potential(n + 1, INF);
    for (int i = 1; i <= n; i++) E.push_back(edge(0, i, 0));

    assert(bellman_ford(n, 0, E, potential));
    for (int i = 1; i <= n; i++) E.pop_back();

    for (int i = 1; i <= n; i++){
        vector <long long> dis = dijkstra(n, i, E, potential);
        for (int j = 1; j <= n; j++){
            ar[i][j] = dis[j];
        }
    }
}

long long ar[MAX][MAX];

int main(){
    vector <struct edge> E;
    E.push_back(edge(1, 2, 2));
    E.push_back(edge(2, 3, -15));
    E.push_back(edge(1, 3, -10));

    int n = 3;
    johnson(n, ar, E);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            printf("%d %d = %lld\n", i, j, ar[i][j]);
        }
    }
    return 0;
}
