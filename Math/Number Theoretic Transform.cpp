const ll mod=786433;

vi getdivs(int p)
{
	int q=p-1;
	vi div;
	for(int j=2; j*j<=q; j++)
	{
		if(q%j==0)
		{
			div.pb(j);
			while(q%j==0) q/=j;
		}
	}
	if(q!=1) div.pb(q);
	return div;
}

bool check(int e, int p, vi divs)
{
	for(auto d: divs)
	{
		if(bigmod((ll)e,(ll)(p-1)/d,(ll)p)==1)
			return false;
	}
	return true;
}

int getRoot(int p)
{
	int e=2;
	vi divs=getdivs(p);
	while(!check(e,p,divs)) e++;
	return e;
}

/* getRoot(mod) returns a value which is used as prr in the following code
 and G in the next one */
// Code 1
ll ipow(ll a, ll b, ll m = mod)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return ret;
}
namespace fft{
	typedef ll base;
	void fft(vector<base> &a, bool inv){
		int n = a.size(), j = 0;
		vector<base> roots(n/2);
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		int prr = 10; // Got from calling getRoot(mod);
		int ang = ipow(prr, (mod - 1) / n);
		if(inv) ang = ipow(ang, mod - 2);
		for(int i=0; i<n/2; i++){
			roots[i] = (i ? (1ll * roots[i-1] * ang % mod) : 1);
		}
		for(int i=2; i<=n; i<<=1){
			int step = n / i;
			for(int j=0; j<n; j+=i){
				for(int k=0; k<i/2; k++){
					base u = a[j+k], v = a[j+k+i/2] * roots[step * k] % mod;
					a[j+k] = (u+v+mod)% mod;
					a[j+k+i/2] = (u-v+mod)%mod;
				}
			}
		}
		if(inv) for(int i=0; i<n; i++) a[i] *= ipow(n, mod-2), a[i] %= mod;
	}
	vector<ll> multiply(vector<ll> &v, vector<ll> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 2; while(n < v.size() + w.size()) n <<= 1;
		fv.resize(n); fw.resize(n);
		fft(fv, 0); fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<ll> ret(n);
		for(int i=0; i<n; i++) ret[i] = fv[i];
		return ret;
	}
}

// Code 2
struct NTT
{
	vi A, B, w[2], rev;
	ll P, M, G;
	NTT(ll mod) {P=mod; G=10;}
	void init(ll n)
	{
		for(M=2; M<n; M<<=1);
		M<<=1;
		A.resize(M); B.resize(M);
		w[0].resize(M); w[1].resize(M); rev.resize(M);

		for(ll i=0; i<M; i++)
		{
			ll x=i, &y=rev[i];
			y=0;
			for(ll k=1; k<M; k<<=1, x>>=1)
				(y<<=1)|=(x&1);
		}

		ll x=bigmod(G,(P-1)/M,mod);
		ll y=bigmod(x,P-2,mod);

		w[0][0]=w[1][0]=1LL;

		for(ll i=1; i<M; i++)
		{
			w[0][i]=(w[0][i-1]*x)%P;
			w[1][i]=(w[1][i-1]*y)%P;
		}
	}
	void ntransform(vector<ll> &a, ll f)
	{
		for(ll i=0; i<M; i++)
		{
			if(i<rev[i]) swap(a[i], a[rev[i]]);
		}
		for(ll i=1; i<M; i<<=1)
		{
			for(ll j=0, t=M/(i<<1); j<M; j+=(i<<1))
			{
				for(ll k=0, l=0; k<i; k++, l+=t)
				{
					ll x=a[j+k+i]*1LL*w[f][l]%P;
					ll y=a[j+k];
					a[j+k+i]=y-x<0?y-x+P:y-x;
					a[j+k]=y+x>=P?y+x-P:y+x;
				}
			}
		}
		if(f)
		{
			ll x=bigmod(M,P-2,mod);
			for(ll i=0; i<M; i++) a[i]=a[i]*1LL*x%P;
		}
	}
	void multiply(vector<ll> &X, vector<ll> &Y, vector<ll> &res)
	{
		init(max(X.size(),Y.size()));
		for(ll i=0; i<M; i++) A[i]=B[i]=0;
		for(ll i=0; i<X.size(); i++) A[i]=X[i];
		for(ll i=0; i<Y.size(); i++) B[i]=Y[i];
		ntransform(A,0);
		ntransform(B,0);
		res.clear();
		res.resize(M);
		for(ll i=0; i<M; i++) res[i]=A[i]*1LL*B[i]%P;
		ntransform(res,1);
	}
};