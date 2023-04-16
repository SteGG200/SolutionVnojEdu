#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<ll> 
#define pii pair<ll,ll>
#define bit(i,mask) mask & (1<<i)
#define bon(i,mask) mask | (1<<i)
#define boff(i,mask) mask & ~(1<<i)
#define flip(i,mask) mask ^= (1<<i)
#define fi first 
#define se second 
#define all(a) (a).begin(), (a).end()
#define gcd __gcd
#define mset(a,v) memset(a, v, sizeof(a))
#define spc " "
#define endl '\n' 
const int MN1 = 1e6 + 5, MN2 = 1e4 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 3e18L + 5;

ll n,m,k;
struct matrix{
  vector<vi> mat = vector<vi>(n,vi(n,INF)); 
  matrix operator *(const matrix &b){
    matrix res; matrix a = *this;
    for(ll i = 0;i < n;++i)
      for(ll j = 0;j < n;++j)
        for(ll k = 0;k < n;++k)
          res.mat[i][j] = min(res.mat[i][j],a.mat[i][k] + b.mat[k][j]);
    return res;
  }
};

matrix binpow(matrix a,ll k){
  matrix res;
  for(ll i = 0;i < n;++i) res.mat[i][i] = 0;
  for(;k > 0;k >>= 1){
    if(k%2) res = res * a;
    a = a * a; 
  }
  return res;
}

void solve(){
  cin>>n>>m>>k; 
  matrix adj;
  while(m--){
    ll u,v,c; cin>>u>>v>>c; 
    adj.mat[u-1][v-1] = c; 
  }
  adj = binpow(adj,k);

  ll ans = INF;
  for(ll i = 0;i < n;++i) 
    for(ll j = 0;j < n;++j)
      ans = min(ans,adj.mat[i][j]);
  if(ans >= INF/2) cout<<"IMPOSSIBLE"<<endl;
  else cout<<ans<<endl;
}

int main(){
  cin.tie(0) -> sync_with_stdio(0);
  //freopen("i.inp", "r", stdin);
  //freopen("o.out", "w", stdout);
  ll t = 1; //cin>>t;
  while(t--){
    solve();
  }
  return 0;
}

