#include <bits/stdc++.h>
// #define MOD 1058375681
const int inf = 1e9 + 7;

using namespace std;

multiset<long> merge(const multiset<long> &A, const multiset<long> &B){
	multiset<long>::iterator itA = A.begin();
	multiset<long>::iterator itB = B.begin();
	multiset<long> result;
	while(itA != A.end() && itB != B.end()){
		if((*itA) < (*itB)){
			result.insert((*itA));
			itA++;
		}else{
			result.insert((*itB));
			itB++;
		}
	}
	while(itA != A.end()){
		result.insert((*itA));
		itA++;
	}
	while(itB != B.end()){
		result.insert((*itB));
		itB++;
	}
	return result;
}

void build(vector<multiset<long>> &st, const vector<long> &arr, long l, long r, long id){
	if(l == r){
		st[id - 1].insert(arr[l - 1]);
		return;
	}

	long mid = (l + r) >> 1;
	build(st, arr, l, mid, 2*id);
	build(st, arr, mid + 1, r, 2*id + 1);

	st[id - 1] = merge(st[2*id - 1], st[2*id]);
}

void update(vector<multiset<long>> &st, const vector<long> &arr,long l, long r, long id, long i, long value){
	if(l > i || r < i) return;

	if(l == r){
		auto it = st[id - 1].upper_bound(arr[i - 1]);
		it--;
		st[id - 1].erase(it);
		st[id - 1].insert(value);
		return;
	}

	long mid = (l + r) >> 1;
	update(st, arr, l, mid, 2*id, i, value);
	update(st, arr, mid + 1, r, 2*id + 1, i, value);

	auto it = st[id - 1].upper_bound(arr[i - 1]);
	it--;
	st[id - 1].erase(it);
	st[id - 1].insert(value);
}

long get(const vector<multiset<long>> &st, long l, long r, long id, long u, long v, long k){
	if(l > v || r < u) return inf;

	if(l >= u && r <= v){
		auto it = st[id - 1].lower_bound(k);
		if(it == st[id - 1].end()) return inf;
		return (*it);
	}

	long mid = (l + r) >> 1;
	long left = get(st, l, mid, 2*id, u, v, k);
	long right = get(st, mid + 1, r, 2*id + 1, u, v, k);

	return min(left, right);
}

int main(){
	long n, m;
	cin >> n >> m;
	vector<long> arr(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	vector<multiset<long>> SegmentTree(4*n);
	build(SegmentTree, arr, 1, n, 1);
	while(m--){
		int type;
		cin >> type;
		if(type == 1){
			long i, u;
			cin >> i >> u;
			update(SegmentTree, arr, 1, n, 1, i, u);
			arr[i - 1] = u;
		}else{
			long l, r, k;
			cin >> l >> r >> k;
			long result = get(SegmentTree, 1, n, 1, l, r, k);
			cout << ((result == inf) ? -1 : result) << endl;
		}
	}

	return 0;
}
