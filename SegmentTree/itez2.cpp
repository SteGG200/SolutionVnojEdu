#include <bits/stdc++.h>
#define MOD 1058375681

using namespace std;

void update(vector<long> &st, long l, long r, long id, long i, long value){
	if(l > i || r < i) return;

	if(l == r){
		st[id - 1] = value;
		return;
	}

	long mid = (l + r) >> 1;
	update(st, l, mid, 2*id, i, value);
	update(st, mid + 1, r, 2*id + 1, i, value);

	st[id - 1] = st[2*id - 1] + st[2*id];
}

long long get(const vector<long> &st, long l, long r, long id, long u, long v){
	if(l > v || r < u) return 0;

	if(l >= u && r <= v) return st[id - 1];

	long mid = (l + r) >> 1;
	long long left = get(st, l, mid, 2*id, u, v);
	long long right = get(st, mid + 1, r, 2*id + 1, u, v);

	return left + right;
}

int main(){
	long n, q;
	cin >> n >> q;
	vector<long> arr(n);
	vector<long> SegmentTree(4*n);
	while(q--){
		int type, a, b;
		cin >> type >> a >> b;
		if(type == 1){
			update(SegmentTree, 1, n, 1, a, b);
		}else{
			cout << get(SegmentTree, 1, n, 1, a, b) << endl;
		}
	}

	return 0;
}
