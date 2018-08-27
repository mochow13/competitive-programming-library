/*Given an undirected graph G = (V, E), we define a cut of G to be a partition
of V into two non-empty sets A and B. Earlier, when we looked at network
flows, we worked with the closely related definition of an s-t cut: there, given
a directed graph G = (V, E) with distinguished source and sink nodes s and t,
an s-t cut was defined to be a partition of V into sets A and B such that s ∈ A
and t ∈ B. Our definition now is slightly different, since the underlying graph
is now undirected and there is no source or sink.
This problem can be solved by max-flow. First we remove undirected edges and replace
them by two opposite directed edge. Now we fix a node s. Then we consider each of
the n nodes as t and run max-flow. The minimum of those values is the answer.
This is O(n^3).
*/

struct Stoer_Wagner{
  vector <vl> weights;
  Stoer_Wagner(ll N){
    weights.resize(N,vl(N,0));
  }
  void AddEdge(ll from, ll to, ll cap){
    weights[from][to]+=cap;
    weights[to][from]+=cap;
  }
  pair<ll, vl> GetMinCut() {
    ll N = weights.size();
    vl used(N), cut, best_cut;
    ll best_weight = -1;

    for (ll phase = N-1; phase >= 0; phase--) {
      vl w = weights[0];
      vl added = used;
      ll prev, last = 0;
      for (ll i = 0; i < phase; i++) {
        prev = last;
        last = -1;
        for (ll j = 1; j < N; j++)
    if (!added[j] && (last == -1 || w[j] > w[last])) last = j;
        if (i == phase-1) {
          for (ll j = 0; j < N; j++) weights[prev][j] += weights[last][j];
          for (ll j = 0; j < N; j++) weights[j][prev] = weights[prev][j];
          used[last] = true;
          cut.push_back(last);
          if (best_weight == -1 || w[last] < best_weight) {
            best_cut = cut;
            best_weight = w[last];
          }
        } else {
            for (ll j = 0; j < N; j++)
              w[j] += weights[last][j];
            added[last] = true;
        }
      }
    }
    return make_pair(best_weight, best_cut);
  }
};

int main() {
  ll T;
  sl(T);
  f(t,1,T+1){
    ll N,M;
    sll(N,M);
    Stoer_Wagner SW(N);
    f(i,0,M){
      ll a,b,c;
      slll(a,b,c);
      SW.AddEdge(a-1,b-1,c);
    }
    pf("Case #%lld: ",t); pfl(SW.GetMinCut().x);
  }
}
