#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MOD 1000000007

const int inf = 1e9 + 7;
const int maxn = 1e5 + 5;

int n, m;
int arr[maxn];

struct Node{
	int add, mul;
	Node(){};
	Node(int _a, int _m) : add(_a), mul(_m) {};
};

struct Segtree{
	vector<int> st;
	vector<Node> lazy;
	Segtree(int _len = 0){
		st.assign(_len * 4, 0);
		lazy.assign(_len * 4, {0, 1});
	}

	void build(int l, int r, int id){
		if(l == r){
			st[id - 1] = arr[l - 1];
			return;
		}
		
		int mid = (l + r) >> 1;
		build(l, mid, 2*id);
		build(mid + 1, r, 2*id + 1);
		st[id - 1] = (st[2*id - 1] + st[2*id]) % MOD;
	}

	void fix(int l, int r, int id){
		if(lazy[id - 1].add == 0 && lazy[id - 1].mul == 1) return;

		st[id - 1] = (lazy[id - 1].mul * st[id - 1]) % MOD;
		st[id - 1] = (lazy[id - 1].add * (r - l + 1) + st[id - 1]) % MOD;
		if(l != r){
			lazy[2*id - 1].mul = (lazy[id - 1].mul * lazy[2*id - 1].mul) % MOD;
			lazy[2*id].mul = (lazy[id - 1].mul * lazy[2*id].mul) % MOD;
			lazy[2*id - 1].add = ((lazy[id - 1].mul * lazy[2*id - 1].add) % MOD + lazy[id - 1].add) % MOD;
			lazy[2*id].add = ((lazy[id - 1].mul * lazy[2*id].add) % MOD + lazy[id - 1].add) % MOD;
		}
		lazy[id - 1].add = 0;
		lazy[id - 1].mul = 1;
	}

	void update(int l, int r, int id, int u, int v, int type, int val){
		fix(l, r, id);
		if(l > v || r < u) return;
		if(u <= l && r <= v){
			if(type == 1){
				lazy[id - 1].add = (val + lazy[id - 1].add) % MOD;
			}else if(type == 2){
				lazy[id - 1].mul = (val * lazy[id - 1].mul) % MOD;
				lazy[id - 1].add = (val * lazy[id - 1].add) % MOD;
			}else{
				lazy[id - 1].mul = 0;
				lazy[id - 1].add = val;
			}
			fix(l, r, id);
			return;
		}

		int mid = (l + r) >> 1;
		update(l, mid, 2*id, u, v, type, val);
		update(mid + 1, r, 2*id + 1, u, v, type, val);

		st[id - 1] = (st[2*id - 1] + st[2*id]) % MOD;
	}

	int get(int l, int r, int id, int u, int v){
		fix(l, r, id);
		if(l > v || r < u) return 0;
		if(u <= l && r <= v) return st[id - 1];
		int mid = (l + r) >> 1;
		int left = get(l, mid, 2*id, u, v);
		int right = get(mid + 1, r, 2*id + 1, u, v);
		return (left + right) % MOD;
	}
};

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	Segtree st(n);
	st.build(1, n, 1);
	while(m--){
		int type, l, r;
		cin >> type >> l >> r;
		if(type == 4){
			cout << st.get(1, n, 1, l, r) << endl;
		}else{
			int x;
			cin >> x;
			st.update(1, n, 1, l, r, type, x);
		}
	}

	return 0;
}
