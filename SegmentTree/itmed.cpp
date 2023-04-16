#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

void update(vector<long long> &st, long l, long r, long id, long i, long value){
	if(l > i || r < i) return;

	if(l == r){
		st[id - 1] = value;
		return;
	}

	long mid = (l + r) >> 1;
	update(st, l, mid, 2*id, i, value);
	update(st, mid + 1, r, 2*id + 1, i, value);

	st[id - 1] = max(st[2*id - 1], st[2*id]);
}

long long get(const vector<long long> &st, long l, long r, long id, long u, long v){
	if(l > v || r < u) return 0;

	if(l >= u && r <= v) return st[id - 1];

	long mid = (l + r) >> 1;
	long long left = get(st, l, mid, 2*id, u, v);
	long long right = get(st, mid + 1, r, 2*id + 1, u, v);

	return max(left, right);
}

int main(){
	long n, k;
	cin >> n >> k;
	vector<pair<long, long>> arr(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i].first;
		arr[i].second = i + 1;
	}
	vector<long long> SegmentTree(4*n);
	for(int i = arr.size() - 1; i >= 0; i--){
		long left = (arr[i].second < n) ? arr[i].second + 1 : n;
		long right = (arr[i].second <= n - k) ? arr[i].second + k : n;
		long long maxValue = get(SegmentTree, 1, n, 1, left, right);
		update(SegmentTree, 1, n, 1, arr[i].second, maxValue + arr[i].first);
	}
	if(SegmentTree[0] < 0) cout << 0 << endl;
	else cout << SegmentTree[0] << endl;

	return 0;
}
