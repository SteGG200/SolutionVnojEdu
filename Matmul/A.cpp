#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld double
#define all(a) (a).begin(), (a).end()
#define vi vector<ll>
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define fi first
#define se second
#define gcd __gcd
#define mset(a,v) memset(a, v, sizeof(a))
#define endl '\n'
#define spc " "

const int MN1 = 1e6 + 5,MN2 = 1e4 + 5,LOG = 27;
const ll MOD = 1e9 + 7,INF = 1e9;

struct matrix{
  vector<vector<ld>> dp;
  ll row(){return dp.size();} ll col(){return dp[0].size();}
  matrix () {}
  matrix(ll r,ll c): dp(r,vector<ld>(c,0)) {}
  matrix operator *(matrix b){
    matrix a = *this;
    matrix res(a.row(),b.col());
    for(ll i = 0;i < a.row();++i)
      for(ll j = 0;j < b.col();++j)
        for(ll k = 0;k < a.col();++k)
          res.dp[i][j] += a.dp[i][k]*b.dp[k][j];
    return res;
  }
};
matrix binpow(matrix a,ll exp){
  if(exp <= 1) return a;
  matrix t = binpow(a,exp >> 1);
  t = t*t; 
  if(exp&1) return a*t;
  else return t;
}

void out(matrix a){
  for(ll i = 0;i < a.row();++i){
    for(ll j = 0;j < a.col();++j)
      cout<<fixed<<setprecision(10)<<a.dp[i][j]<<spc;
    cout<<endl;
  }
  cout<<endl;
}
ll n; ld p;
void solve(){
  cin>>n>>p;
  matrix a,base; 
  //happyge - sadge 
  a.dp = {{1},{0}}; 
  base.dp = {{1 - p,p},
             {p,1 - p}};
  base = binpow(base,n); 
  a = a*base; 
  //out(base); out(a);
  cout<<fixed<<setprecision(10)<<a.dp[0][0];
}

signed main(){
  cin.tie(0) -> sync_with_stdio(0);
  //freopen("i.inp","r",stdin);
  //freopen("o.out","w",stdout);
  ll t = 1; //cin>>t;
  while(t--) solve();
  cerr << endl << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
}

