int n;  // n is the number of dictionary word
string s,p;  // dictionary words are inputted in p, s is the traversed text

#define MAX_NODE 250004

map<char,int> node[MAX_NODE]; // use 2d array maybe?
int root, nnode, link[MAX_NODE], endof[504], travis[MAX_NODE];
pii level[MAX_NODE];

void init()
{
    root=0;
    nnode=0;
    travis[root]=0;  // number of time a node is traversed by s
    level[root]=MP(0,root);  // level, node
    node[root].clear();
}

void insertword(int idx)
{
    int len=p.size();
    int now=root;

    FOR(i,0,len)
    {
        // use map.find()
        if(!node[now][p[i]])
        {
            node[now][p[i]]=++nnode;
            node[nnode].clear();

            travis[nnode]=0;
            level[nnode]=MP(level[now].first+1,nnode);
        }

        now=node[now][p[i]];
    }

    endof[idx]=now;  // end of dictionary word idx
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
        
        itrALL(node[u],it)
        {
            char ch=it->first;
            int v=it->second;
            int j=link[u];

            // use map.find()
            while(j!=-1 && !node[j][ch])
                j=link[j];

            if(j!=-1) link[v]=node[j][ch];
            else link[v]=0;

            q.push(v);
        }
    }
}

void traverse()
{
    int len=s.size();
    int now=root;

    travis[root]++;

    FOR(i,0,len)
    {
        // use map.find()
        while(now!=-1 && !node[now][s[i]])
            now=link[now];

        if(now!=-1) now=node[now][s[i]];
        else now=0;

        travis[now]++;
    }

    sort(level,level+nnode+1,greater<pii>());

    FOR(i,0,nnode+1)
    {
        now=level[i].second;
        travis[link[now]]+=travis[now];
    }
}

void driver()
{
    init();
    FOR(i,0,n)
    {
        // input p
        insertword(i);
    }
    // input s
    push_links();
    traverse();
    // number of occurence of word i in s is travis[endof[i]]
}
