#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

void build(vector<int> &st, const vector<int> &arr, int l, int r, int id){
	if(l == r){
		st[id - 1] = arr[l - 1];
		return ;
	}

	int mid = (l + r) >> 1;
	build(st, arr, l, mid, 2*id);
	build(st, arr, mid + 1, r, 2*id + 1);

	st[id - 1] = max(st[2*id - 1], st[2*id]);
}

void update(vector<int> &st, int l, int r, int id, int i, int value){
	if(l > i || r < i) return;

	if(l == r){
		st[id - 1] = value;
		return;
	}

	int mid = (l + r) >> 1;
	update(st, l, mid, 2*id, i, value);
	update(st, mid + 1, r, 2*id + 1, i, value);

	st[id - 1] = max(st[2*id - 1], st[2*id]);
}

int get(const vector<int> &st, int l, int r, int id, int u, int v){
	if(l > v || r < u) return -inf;

	if(l >= u && r <= v) return st[id - 1];

	int mid = (l + r) >> 1;
	int left = get(st, l, mid, 2*id, u, v);
	int right = get(st, mid + 1, r, 2*id + 1, u, v);

	return max(left, right);
}

int main(){
	int n;
	cin >> n;
	vector<int> arr(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	vector<int> SegmentTree(4*n);
	build(SegmentTree, arr, 1, n, 1);
	int q;
	cin >> q;
	while(q--){
		int type, x, y;
		cin >> type >> x >> y;
		if(type == 1){
			update(SegmentTree, 1, n, 1, x, y);
		}else{
			cout << get(SegmentTree, 1, n, 1, x, y) << endl;
		}
	}

	return 0;
}