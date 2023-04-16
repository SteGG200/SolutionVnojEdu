#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<ll,ll> 
#define vi  vector<ll> 
#define all(a) (a).begin(), (a).end()
#define fi first
#define se second
#define gcd __gcd
#define mset(a) memset(a, 0, sizeof(a))
#define endl '\n'
#define spc " "

const int MN1 = 1e6 + 5,MN2 = 1e4 + 5,LOG = 30;
const ll MOD = 1e9 + 7,INF = 1e9;

//chuan bi truoc A^(2^i)
//A^k
//ok

struct matrix{
  vector<vi> dp;
  ll row(){return dp.size();} ll col(){return dp[0].size();}
  matrix () {}
  matrix(ll r,ll c): dp(r,vi(c,0)) {}
  matrix operator *(matrix b){
    matrix a = *this;
    matrix res(a.row(),b.col());
    for(ll i = 0;i < a.row();++i)
      for(ll j = 0;j < b.col();++j)
        for(ll k = 0;k < a.col();++k)
          res.dp[i][j] = (res.dp[i][j] + a.dp[i][k]*b.dp[k][j]) % MOD;
    return res;
  }
  matrix operator +(matrix b){
    matrix a = *this;
    matrix res(a.row(),a.col());
    for(ll i = 0;i < a.row();++i)
      for(ll j = 0;j < a.col();++j)
        res.dp[i][j] = (a.dp[i][j] + b.dp[i][j]) % MOD;
    return res;
  }
};

matrix binpow(matrix a,ll k){
  if(k == 1) return a; 
  matrix t = binpow(a,k >> 1);
  t = t*t;;
  if(k&1) return a*t;
  else return t;
}

ll n,m,q,dp[LOG][MN1];
matrix a[LOG];

void solve(){
  cin>>n>>m>>q;
  matrix adj(n,n);
  while(m--){
    ll u,v; cin>>u>>v;
    adj.dp[u - 1][v - 1]++;
  }
  for(ll i = 0;i < LOG;++i){
    if(i == 0) a[i] = adj;
    else a[i] = a[i-1]*a[i-1];
  }
  while(q--){
    ll u,v,k; cin>>u>>v>>k;
    matrix res(1,n);
    res.dp[0][u-1] = 1; 
    for(ll i = 0;i < LOG;++i)
      if(k&(1<<i))
        res = res * a[i];
    cout<<res.dp[0][v-1]<<endl;
  }
 
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);  
  
  //freopen("i.inp","r",stdin);
  //freopen("o.out","w",stdout);
  ll t = 1; //cin>>t;
  while(t--){

    solve();
  }

  return 0;
}

