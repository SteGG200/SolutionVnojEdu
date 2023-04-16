#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
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
const int MN1 = 1e6 + 5,MN2 = 1e4 + 5,LOG = 20;
const ll MOD = 4294967296,INF = 0x3f3f3f3f3f;

struct matrix{
  ll n,m; vector<vi> dp; 
  matrix(ll _n,ll _m){
    n = _n,m = _m;
    dp = vector<vi>(n,vi(m,0));
  }
  ll row(){ return n;} ll col(){ return m;}
};

matrix mul(matrix a,matrix b){
  matrix res(a.row(),b.col());
  for(ll i = 0;i < a.row();++i)
    for(ll j = 0;j < b.col();++j)
      for(ll k = 0;k < a.col();++k){
        res.dp[i][j] = (res.dp[i][j]+a.dp[i][k]*b.dp[k][j]) % MOD;
      }
  return res;
}

matrix binpow(matrix a,ll k){
  if(k == 1) return a; 
  matrix t = binpow(a,k >> 1);
  t = mul(t,t);
  if(k&1) return mul(a,t);
  return t;
}

ll k;

bool check(ll row,ll col){
  return 0 <= min(row,col) && max(row,col) < 8;
}

void solve(){
  cin>>k;
  matrix adj(65,65);
  for(ll i = 0;i <= 64;++i) adj.dp[i][64] = 1; 
  for(ll row = 0;row < 8;++row)
    for(ll col = 0;col < 8;++col)
      for(int dr : {-2,-1,1,2})
        for(int dc : {-2,-1,1,2}){
          if(abs(dr) != abs(dc)){
            ll new_row = row + dr,
               new_col = col + dc;
            if(check(new_row,new_col))
              adj.dp[8*row + col][8*new_row + new_col] = 1;
            }
        }
  adj = binpow(adj,k+1);
  //for(ll i = 0;i < res.row();++i){
  //  for(ll j = 0;j < res.col();++j)
  //    cout<<res.dp[i][j]<<spc;
  //  cout<<endl;
  //}
  cout<<adj.dp[0][64];
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

