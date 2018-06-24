#include <bits/stdc++.h>

using namespace std;

// sa[i] -> ith smallest suffix of the string (indexed from 0)
// height[i] -> Longest common substring between Suffix(i) and Suffix(i-1), indexed
// from i=2.
// rak[i] -> The position of i th index of the main string in height array.
// 0 or 1 based ranking (check)

const int N = 2e6+5;
int wa[N],wb[N],wv[N],wc[N];
int r[N],sa[N],rak[N], height[N];

int cmp(int *r,int a,int b,int l)
{
      return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int *r,int *sa,int n,int m)
{
      int i,j,p,*x=wa,*y=wb,*t;
      for( i=0;i<m;i++) wc[i]=0;
      for( i=0;i<n;i++) wc[x[i]=r[i]] ++;
      for( i=1;i<m;i++) wc[i] += wc[i-1];
      for( i= n-1;i>=0;i--)sa[--wc[x[i]]] = i;
      for( j= 1,p=1;p<n;j*=2,m=p){
            for(p=0,i=n-j;i<n;i++)y[p++] = i;
            for(i=0;i<n;i++)if(sa[i] >= j) y[p++] = sa[i] - j;
            for(i=0;i<n;i++)wv[i] = x[y[i]];
            for(i=0;i<m;i++) wc[i] = 0;
            for(i=0;i<n;i++) wc[wv[i]] ++;
            for(i=1;i<m;i++) wc[i] += wc[i-1];
            for(i=n-1;i>=0;i--) sa[--wc[wv[i]]] = y[i];
            for(t=x,x=y,y=t,p=1,x[sa[0]] = 0,i=1;i<n;i++) x[sa[i]]= cmp(y,sa[i-1],sa[i],j) ? p-1:p++;
 
      }
}

void calheight(int *r,int *sa,int n)
{
 
      int i,j,k=0;
      for(i=1;i<=n;i++) rak[sa[i]] = i;
      for(i=0;i<n;height[rak[i++]] = k ) {
 
            for(k?k--:0, j=sa[rak[i]-1] ; r[i+k] == r[j+k] ; k ++) ;
      }
 
}

int dp[N][22];

void initRMQ(int n)
{
      for(int i= 1;i<=n;i++) dp[i][0] = height[i];
      for(int j= 1; (1<<j) <= n; j ++ ){
            for(int i = 1; i + (1<<j) - 1 <= n ; i ++ ) {
                  dp[i][j] = min(dp[i][j-1] , dp[i + (1<<(j-1))][j-1]);
            }
      }
 
}
int askRMQ(int L,int R)
{
      int k = 0;
      while((1<<(k+1)) <= R-L+1) k++;
      return min(dp[L][k], dp[R - (1<<k) + 1][k]);
}

int main()
{

	return 0;
}