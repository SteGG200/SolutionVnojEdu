#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vii vector<ll>
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
const ll INF = 0x3f3f3f3f3f;

//dp[l][j] += dp[l+1][j'] 
struct matrix{
  ll n,m; vector<vii> mat;
  matrix(ll _n,ll _m){ 
    n = _n,m = _m; 
    mat = vector<vii>(n,vii(m));
  } 
  ll row(){ return n;} 
  ll col(){ return m; } 
};

matrix mul(matrix a,matrix b){
  matrix c(a.row(),b.col());
  for(ll i = 0;i < a.row();++i)
    for(ll j = 0;j < b.col();++j)
      for(ll k = 0;k < a.col();++k)
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

ll n;
void solve(){
  cin>>n;
  matrix a(2,2),b(2,1);
  a.mat = {{19,7},
           {6,20}};
  matrix ans(2,2);
  if(n > 1) ans = binpow(a,n);
  else ans = a; 
  cout<<ans.mat[0][0];
  //for(ll i = 0;i < ans.row();++i){
  //  for(ll j = 0;j < ans.col();++j)
  //    cout<<ans.mat[i][j]<<spc; 
  //  cout<<endl;
  //}
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

