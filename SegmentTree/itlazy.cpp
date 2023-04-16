#include <bits/stdc++.h>
const int inf = 1e9 + 7;

using namespace std;

void build(vector<long long> &st, const vector<long> &arr, long l, long r, long id){
	if(l == r){
		st[id - 1] = arr[l - 1];
		return;
	}

	long mid = (l + r) >> 1;
	build(st, arr, l, mid, 2*id);
	build(st, arr, mid + 1, r, 2*id + 1);

	st[id - 1] = max(st[2*id - 1], st[2*id]);
}

void fix(vector<long long> &lazy, vector<long long> &st, long l, long r, long id){
	if(!lazy[id - 1]) return;

	st[id - 1] += lazy[id - 1];

	if(l != r){
		lazy[2*id - 1] += lazy[id - 1];
		lazy[2*id] += lazy[id - 1];
	}

	lazy[id - 1] = 0;
}

void update(vector<long long> &st, vector<long long> &lazy, long l, long r, long id, long u, long v, long val){
	fix(lazy, st, l, r, id);

	if(l > v || r < u) return;

	if(l >= u && r <= v){
		lazy[id - 1] += val;
		fix(lazy, st, l, r, id);
		return;
	}

	long mid = (l + r) >> 1;
	update(st, lazy, l, mid, 2*id, u, v, val);
	update(st, lazy, mid + 1, r, 2*id + 1, u, v, val);

	st[id - 1] = max(st[2*id - 1], st[2*id]);
}

long long get(vector<long long> &st, vector<long long> &lazy, long l, long r, long id, long u, long v){
	fix(lazy, st, l, r, id);
	if(l > v || r < u) return -inf;

	if(l >= u && r <= v){
		return st[id - 1];
	}

	long mid = (l + r) >> 1;
	long long left = get(st, lazy, l, mid, 2*id, u, v);
	long long right = get(st, lazy, mid + 1, r, 2*id + 1, u, v);

	return max(left, right);
}

int main(){
	long n;
	cin >> n;
	vector<long> arr(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	vector<long long> SegmentTree(4*n);
	vector<long long> lazy(4*n);
	build(SegmentTree, arr, 1, n, 1);
	long q;
	cin >> q;
	while(q--){
		int type;
		cin >> type;
		if(type == 1){
			long x, y, val;
			cin >> x >> y >> val;
			update(SegmentTree, lazy, 1, n, 1, x, y, val);
		}else{
			long l, r;
			cin >> l >> r;
			cout << get(SegmentTree, lazy, 1, n, 1, l, r) << endl;
		}
	}

	return 0;
}
