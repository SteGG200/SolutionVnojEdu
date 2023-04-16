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

const int MN1 = 1e6 + 5,MN2 = 1e4 + 5,LOG = 27;
const ll MOD = 1e9 + 7,INF = 1e9;

struct matrix{
  ll a[2][2] = {{0,0},{0,0}}; 
  matrix operator *(matrix b){
    matrix res;
    for(ll i = 0;i < 2;++i)
      for(ll j = 0;j < 2;++j)
        for(ll k = 0;k < 2;++k)
          res.a[i][k] = (res.a[i][k] + a[i][j]*b.a[j][k]) % MOD;
    return res;
  }
  void init(char c){
    a[0][1] = a[1][0] = a[0][0] = a[1][1] = 0;
    for(char ch = 'A'; ch <= 'Z';++ch){
      if(c == '?' || ch == c){
        if(ch == 'H'){
          a[0][1]++;
          a[1][1]++;
        }else if(ch == 'S' || ch == 'D'){
          a[0][0]++;
          a[1][0]++;
        }else if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){
          a[0][1]++;
          a[1][0]++;
        }else{
          a[0][0]++;
          a[1][1]++;
        }   
      }
    }
  } 
};

matrix st[MN1];
ll n,q;
string s;



void solve(){
  cin>>n>>q>>s;
  ll base = 1; 
  while(base < n) base *= 2; 
  for(ll i = 0;i < n;++i)
    st[base + i].init(s[i]);
  for(ll i = n;i < base;++i)
    st[base + i].init('Z');
  for(ll i = base - 1;i >= 1;--i)
    st[i] = st[2*i] * st[2*i + 1];
  cout<<st[1].a[1][1]<<endl;
  while(q--){
    ll i; char c; 
    cin>>i>>c;
    i--;
    st[base + i].init(c);
    for(ll k = (base + i)/2;k >= 1;k /= 2)
      st[k] = st[2*k] * st[2*k + 1];
    cout<<st[1].a[1][1]<<endl;
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

