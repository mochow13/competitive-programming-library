// Suppose we have n<=1000 strings. Total summation of the length of these strings
// can be 1e7. Now we are given queries. In each query, we are given indices of
// two strings and asked if one of them occurs in another as a substring. 
// We need to find this relation efficiently. We will use Aho-Corasick.

// The solution is to build a graph where vertices denote indices of strings and an edge
// from u to v denotes that string[u] occurs in string[v].

#define ALPHABET_SIZE 26
#define MAX_NODE 1e6
int n; // number of strings
string in[N], p;

int node[MAX_NODE][ALPHABET_SIZE]; 
int root, nnode, link[MAX_NODE], termlink[MAX_NODE], terminal[MAX_NODE];
bool graph[N][N];

// termlink[u] = a link from node u to a node which is a terminal node
// terminal node is a node where an ending of an input string occurs
// terminal[node] = the index of the string which ends in node

/* Solution:
// For every node of the Aho-Corasick structure find and remember the 
nearest terminal node (termlink[u]) in the suffix-link path; Once again traverse 
all strings through Aho-Corasick. Every time new symbol is added, add an arc from the node 
corresponding to the current string (in the graph we build, not Aho-Corasick) to 
the node of the graph corresponding to the nearest terminal in the suffix-link path; 
The previous step will build all essential arcs plus 
some other arcs, but they do not affect the next step in any way;
Find the transitive closure of the graph.
*/

void init()
{
    root=0;
    nnode=0;
    ms(terminal,-1);
    ms(termlink,-1);
}

void insertword(int idx)
{
	p=in[idx];
    int len=p.size();
    int now=root;

    FOR(i,0,len)
    {
    	int x=p[i]-'a';

        if(!node[now][x])
        {
            node[now][x]=++nnode;
        }

        now=node[now][x];
    }

    terminal[now]=idx; // string with index idx ends in now
}

void push_links()
{
    queue<int>q;
    link[0]=-1;
    q.push(0);

    while(!q.empty())
    {
        int u=q.front();
        q.pop();

       	for(int i=0; i<ALPHABET_SIZE; i++)
        {
        	if(!node[u][i]) continue;

            int v=node[u][i];
            int j=link[u];
            // use map.find()
            while(j!=-1 && !node[j][i])
            	j=link[j];

            if(j!=-1) link[v]=node[j][i];
            else link[v]=0;

			// Finding nearest terminal nodes
            if(terminal[link[v]]!=-1)
            	termlink[v]=link[v];
            else termlink[v]=termlink[link[v]];

            q.push(v);
        }
    }
}

void buildgraph()
{
	FOR(i,0,n)
	{
		int curr=root;

		FOR(j,0,in[i].size())
		{
			char ch=in[i][j];
			curr=node[curr][(int)ch-'a'];

			int st=curr;
			if(terminal[st]==-1) st=termlink[st];

			for(int k=st; k>=0; k=termlink[k])
			{
				if(terminal[k]==i) continue;
				if(graph[i][terminal[k]]) break;
				graph[i][terminal[k]]=true;

				// cout<<"edge: "<<i<<" "<<terminal[k]<<endl;
			}
		}
	}
}

// Finally, find transitive closure of the graph. If O(n^3) is possible, we can use
// Floyd-Warshall. Otherwise, run dfs from each node and add an edge from current starting
// node to each reachable node. An edge in this transitive closure denotes the occurrence relation.