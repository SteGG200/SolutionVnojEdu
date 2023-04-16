#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<ll,ll>
#define vii vector<ll>
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
const int MN1 = 1e6 + 5, MN2 = 1e3 + 1;
const ll MOD = 1e9 + 7;
const ll INF = 0x3f3f3f3f3f;

//A: mxn
//B: nxp 
//C: mxp

struct matrix{
  ll n,m; vector<vii> mat;
  matrix(ll _n,ll _m){ 
    n = _n,m = _m; 
    mat.assign(n + 1,vii(m + 1,0));
  } 
  ll row(){ return n;} 
  ll col(){ return m; } 
  void inp(){
    for(ll i = 0;i < n;++i)
      for(ll j = 0;j < m;++j) 
        cin>>mat[i][j];
  }
  void out(){
    for(ll i = 0;i < n;++i){
      for(ll j = 0;j < m;++j) 
        cout<<mat[i][j]<<spc;
      cout<<endl;
    }
  }
};

matrix mul(matrix a,matrix b){
  ll arow = a.row(),acol = a.col(),bcol = b.col(); 
  matrix c(arow,bcol);
  for(ll i = 0;i < arow;++i)
    for(ll j = 0;j < bcol;++j)
      for(ll k = 0;k < acol;++k)
        c.mat[i][j] = (c.mat[i][j] + a.mat[i][k]*b.mat[k][j]) % MOD;
  return c;
}

matrix binpow(matrix base,ll exp){
  if(exp == 1) return base; 
  matrix t = binpow(base,exp >> 1); 
  t = mul(t,t); 
  if(exp&1) return mul(base,t);
  else return t; 
}

ll n,m,k;
void solve(){
  cin>>n>>m>>k;
  matrix adj(n,n);
  while(m--){
    ll u,v; cin>>u>>v; 
    adj.mat[u-1][v-1] = 1; 
  }
  adj = binpow(adj,k);
  ll ans = 0;
  for(ll i = 0;i < n;++i)
    for(ll j = 0;j < n;++j)
      ans = (ans + adj.mat[i][j]) % MOD;
  cout<<ans;
}

int main(){
  cin.tie(0) -> sync_with_stdio(0);
  //freopen("i.inp", "r", stdin);
  //freopen("o.out", "w", stdout);
  ll t = 1; //cin>>t;
  while(t--) solve();
  return 0;
}

