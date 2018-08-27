// Assuming vertices are labeled 1...V
const int SIZE=1e5+5;
vi graph[SIZE], rev[SIZE];
bool explored[SIZE];
int leader[SIZE], finish[SIZE], order[SIZE], t = 0, parent = 0;
map <int, bool> truthAssignment;

// running DFS on the reverse graph
void dfs_reverse(int i) {
    explored[i] = true;
    for(vi::iterator it = rev[i].begin(); it != rev[i].end(); it++)
        if(!explored[*it])
            dfs_reverse(*it);
    t++;
    finish[i] = t;
}

// running DFS on the actual graph
void dfs(int i) {
    explored[i] = true;
    leader[i] = parent;
    for(vi::iterator it = graph[i].begin(); it != graph[i].end(); it++)
        if(!explored[*it])
            dfs(*it);
}

// check if u & v are in the same connected component
bool stronglyConnected(int u, int v)    {
    return leader[u] == leader[v];
}

int main()  {
    int i, u, v, N, M;
    // N is the number of variables and M is the number of clauses
    scanf("%d %d", &N, &M);
    for(i=0; i<M; i++)  {
        scanf("%d %d", &u, &v); /*  Each clause is of the form u or v
                                    1 <= x <= N for an uncomplemented variable x
                                    -N <= x <= -1 for a complemented variable x
                                    -x is the complement of a variable x
                                */

    // Internally, complement of variable x is represented as N + x.
        if(u > 0)   {
            if(v > 0)   {
                graph[N+u].push_back(v); graph[N+v].push_back(u);
                rev[v].push_back(N+u); rev[u].push_back(N+v);
            } else  {
                graph[N+u].push_back(N-v); graph[-v].push_back(u);
                rev[N-v].push_back(N+u); rev[u].push_back(-v);
            }
        } else  {
            if(v > 0)   {
                graph[-u].push_back(v); graph[N+v].push_back(N-u);
                rev[v].push_back(-u); rev[N-u].push_back(N+v);
            } else  {
                graph[-u].push_back(N-v); graph[-v].push_back(N-u);
                rev[N-v].push_back(-u); rev[N-u].push_back(-v);
            }
        }
    }

    // run dfs on the reverse graph to get reverse postorder
    memset(explored, false, (2*N + 1)*sizeof(bool));
    for(i=2*N; i>0; i--)  {
        if(!explored[i])
            dfs_reverse(i);
        order[finish[i]] = i;
    }

    // run dfs on the actual graph in reverse postorder
    memset(explored, false, (2*N + 1)*sizeof(bool));
    for(i=2*N; i>0; i--)
        if(!explored[order[i]]) {
            parent = order[i];
            dfs(order[i]);
        }
    // check if a variable and its complement belong in the same SCC in reverse postorder
    // and assign truth values to SCC
    for(i=2*N; i>0; i--)   {
        u = order[i];
        if(u > N)   {
            if(stronglyConnected(u, u-N)) break;
            if(truthAssignment.find(leader[u]) == truthAssignment.end())    {
                truthAssignment[leader[u]] = true;
                truthAssignment[leader[u-N]] = false;
            }
        } else {
            if(stronglyConnected(u, N+u)) break;
            if(truthAssignment.find(leader[u]) == truthAssignment.end())    {
                truthAssignment[leader[u]] = true;
                truthAssignment[leader[N+u]] = false;
            }
        }
    }

    if(i > 0)
        printf("Unsatisfiable\n");
    else    {
        printf("Satisfying assignment :\n");
        for(i=1; i<=N; i++)
            printf("%d : %s\n", i, truthAssignment[leader[i]] ? "true" : "false");
    }

    return 0;
}