/* Problem:
Given n functions yi(x) = a0 + a1x + a2x^2 + a3x^3 and q queries. For each query, you are 
given an integer t and you are required to find out yi (i ≤ i ≤ n) that minimizes the value of yi(t).

Li Chao Tree works for functions that intersect only in one point. Constraints of the problem were
such that there would always be at most on intersecting point between to functions with x>=350. So
we bruteforced for x<350 and built Li Chao Tree for x>=350
*/

const int N=1e5; // Max query points
const int offset=350; // Bruteforce for this limit
struct fun
{
      ll a, b, c, d;
      fun(){a=0, b=0, c=0, d=INF;}
      fun(ll a, ll b, ll c, ll d) : 
            a(a), b(b), c(c), d(d) { }
      ll eval(ll x)
      {
            return a*x*x*x+b*x*x+c*x+d;
      }
} Tree[4*N+5];

ll aux[offset+5];

void init()
{
      ms(aux,63);
      FOR(i,1,4*N) Tree[i]=fun();
}

int compare(ll x, ll y)
{
      if(x<y) return -1;
      return x>y;
}

void update(int node, int l, int r, int x, int y, fun fx)
{
      if(x>r || y<l) return;
      if(x<=l && r<=y)
      {
            // cout<<"x-y: "<<x<<" "<<y<<endl;
            // cout<<"l-r: "<<l<<" "<<r<<endl;

            // fx - new function, Tree[node] - old function
            int mid=(l+r)/2;

            int fl=compare(fx.eval(l),Tree[node].eval(l));
            int fr=compare(fx.eval(r),Tree[node].eval(r));
            int fm1=compare(fx.eval(mid),Tree[node].eval(mid));
            int fm2=compare(fx.eval(mid+1),Tree[node].eval(mid+1));

            // New function is worse for l to r, no point of adding it.
            if(fl>=0 && fr>=0) return;

            // New function is better for l to r, add it
            if(fl<=0 && fr<=0)
            {
                  Tree[node]=fx;
                  return;
            }

            // New function is better for l to mid, add it. Old function can still be
            // better for right segment.
            if(fl<=0 && fm1<=0)
            {
                  // Sending the old function to right segment
                  update(rc,mid+1,r,x,y,Tree[node]);
                  Tree[node]=fx;
                  return;
            }

            // New function is worse for l to mid, but this can be better for right segment.
            if(fl>=0 && fm1>=0)
            {
                  update(rc,mid+1,r,x,y,fx);
                  return;
            }

            // New function worse for mid+1 to r, but can be better for left segment
            if(fm2>=0 && fr>=0)
            {
                  update(lc,l,mid,x,y,fx);
                  return;
            }

            // New function better for mid+1 to r, add it, old function can still be better for left.
            if(fm2<=0 && fr<=0)
            {
                  update(lc,l,mid,x,y,Tree[node]);
                  Tree[node]=fx;
                  return;
            }
      }
      else if(l<r)
      {
            int mid=(l+r)/2;

            update(lc,l,mid,x,y,fx);
            update(rc,mid+1,r,x,y,fx);            
      }
}

ll query(int node, int l, int r, int x)
{
      if(l==r) return Tree[node].eval(x);

      int mid=(l+r)/2;

      ll ret=Tree[node].eval(x);

      if(x<=mid) ret=min(ret,query(lc,l,mid,x));
      else ret=min(ret,query(rc,mid+1,r,x));

      return ret;
}

void calc(fun &fx)
{
      for(int i=0; i<offset; i++)
      {
            aux[i]=min(aux[i],fx.eval(i));
            // prnt(fx.eval(i));
      }
}

int main()
{
      // ios_base::sync_with_stdio(0);
      // cin.tie(NULL); cout.tie(NULL);
      // freopen("in.txt","r",stdin);

      int test, cases = 1;

      scanf("%d", &test);

      int n;

      while(test--)
      {
            scanf("%d", &n);

            init();
            int a, b, c, d;

            FOR(i,0,n)
            {
                  scanf("%d%d%d%d", &d, &c, &b, &a);
                  fun fx=fun(a,b,c,d);
                  calc(fx);
                  update(1,1,N,offset,N,fx);
            }

            int q, x;
            scanf("%d", &q);

            while(q--)
            {
                  scanf("%d", &x);

                  if(x<offset) printf("%lld\n", aux[x]);
                  else
                  {
                        ll out=query(1,1,N,x);
                        printf("%lld\n", out);
                  }
            }
      }
      
      return 0;
}