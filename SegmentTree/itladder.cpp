#include <bits/stdc++.h>
// #define MOD 1058375681
#define MOD 1000000007
const int inf = 1e9 + 7;

using namespace std;

void fix(vector<long long> &st, vector<pair<long long, long long>> &lazy, long l, long r, long id){
	st[id - 1] += (lazy[id - 1].second*(r + l)*(r - l + 1) / 2) % MOD;
	st[id - 1] %= MOD;
	st[id - 1] += (lazy[id - 1].first * (r - l + 1)) % MOD;
	st[id - 1] %= MOD;
	if(l != r){
		lazy[2*id - 1].first = (lazy[id - 1].first + lazy[2*id - 1].first) % MOD;
		lazy[2*id - 1].second = (lazy[id - 1].second + lazy[2*id - 1].second) % MOD;
		lazy[2*id].first = (lazy[id - 1].first + lazy[2*id].first) % MOD;
		lazy[2*id].second = (lazy[id - 1].second + lazy[2*id].second) % MOD;
	}
	lazy[id - 1].first = 0;
	lazy[id - 1].second = 0;
}

void update(vector<long long> &st, vector<pair<long long, long long>> &lazy, long l, long r, long id, long u, long v, long A, long B){
	fix(st, lazy, l, r, id);
	if(l > v || r < u) return ;

	if(l >= u && r <= v){
		lazy[id - 1].first = (1ll*B - 1ll*u*A + 1ll*MOD*MOD) % MOD;
		lazy[id - 1].second = A % MOD;
		fix(st, lazy, l , r, id);
		return;
	}
	
	long mid = (l + r) >> 1;
	update(st, lazy, l, mid, 2*id, u, v, A, B);
	update(st, lazy, mid + 1, r, 2*id + 1, u, v, A, B);

	st[id - 1] = (st[2*id - 1] + st[2*id]) % MOD;
}

long long get(vector<long long> &st, vector<pair<long long , long long>> & lazy, long l, long r, long id, long u, long v){
	fix(st, lazy, l, r, id);
	if(l > v || r < u) return 0;

	if(l >= u && r <= v){
		return st[id - 1] % MOD;
	}

	long mid = (l + r) >> 1;
	long long left = get(st, lazy, l, mid, 2*id, u, v);
	long long right = get(st, lazy, mid + 1, r, 2*id + 1, u, v);

	return (left + right) % MOD;
}

int main(){
	long n, m;
	cin >> n >> m;
	vector<long long> SegmentTree(4*n);
	vector<pair<long long, long long>> lazy(4*n);
	while(m--){
		int type;
		cin >> type;
		if(type == 1){
			long l, r, A, B;
			cin >> l >> r >> A >> B;
			update(SegmentTree, lazy, 1, n, 1, l, r, A, B);
		}else{
			long l, r;
			cin >> l >> r;
			cout << get(SegmentTree, lazy, 1, n, 1, l, r) << endl;
		}
	}

	return 0;
}
