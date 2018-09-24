// Finds a cycle starting from a node u
const int N = 1005;
bool visited[N], instack[N];
stack<int> st;
vi graph[N]; int n;
vpii cycle; // contains the edges of the cycle
bool findCycle(int u)
{
      if(!visited[u])
      {
            visited[u]=true;
            instack[u]=true;
            st.push(u);
            for(auto v: graph[u])
            {
                  if(!visited[v] && findCycle(v)) return true;
                  else if(instack[v])
                  {
                        cycle.pb({u,v});
                        st.pop();
                        int t=u;
                        while(v!=t)
                        {
                              cycle.pb({st.top(),t});
                              t=st.top();
                              st.pop();
                        }
                        return true;
                  }
            }
      }
      instack[u]=false;
      st.pop();      
      return false;
}
void find()
{
      FOR(i,1,n+1)
      {
            ms(visited,false);
            ms(instack,false);
            if(findCycle(i))
            {
                  // A cycle found starting from i
            }
      }
}