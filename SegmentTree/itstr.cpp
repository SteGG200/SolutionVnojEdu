#include <bits/stdc++.h>
#define MOD 1007050321

using namespace std;

const int inf = 1e9 + 7;
const int maxn = 1e5 + 5;

long long pow2[maxn];

struct Node{
	long long value;
	int len;
	int w;
	Node(){
		value = 0;
		len = 0;
		w = 0;
	}
};

struct SegTree{
	vector<Node> st;
	SegTree(int _len = 0){
		st.resize(_len*4);
	}

	void build(string &s, int l, int r, int id){
		if(l == r){
			st[id - 1].value = s[l - 1] - '0';
			st[id - 1].len = 1;
			st[id - 1].w = 1;
			return;
		}

		int mid = (l + r) >> 1;
		build(s, l, mid, 2*id);
		build(s, mid + 1, r, 2*id + 1);

		st[id - 1].w = st[2*id - 1].w + st[2*id].w;
		st[id - 1].len = st[2*id - 1].len + st[2*id].len;
		st[id - 1].value = ((st[2*id - 1].value * pow2[st[2*id].len]) % MOD + st[2*id].value) % MOD;
	}

	int DAC(int l, int r, int id, int target){
		if(l == r) return l;

		int mid = (l + r) >> 1;
		if(target <= st[2*id - 1].w) return DAC(l, mid, 2*id, target);
		else return DAC(mid + 1, r, 2*id + 1, target - st[2*id - 1].w);
	}

	void update(int l, int r, int id, int pos){
		if(l > pos || r < pos) return;
		st[id - 1].len--;
		if(l == r){
			st[id - 1].value = st[id - 1].w = 0;
			return;
		}
		int mid = (l + r) >> 1;

		update(l, mid, 2*id, pos);
		update(mid + 1, r, 2*id + 1, pos);

		st[id - 1].w = st[2*id - 1].w + st[2*id].w;
		st[id - 1].len = st[2*id - 1].len + st[2*id].len;
		st[id - 1].value = ((st[2*id - 1].value * pow2[st[2*id].len]) % MOD + st[2*id].value) % MOD;
	}

	Node get(int l, int r, int id, int u, int v){
		if(l > v || r < u){
			Node temp;
			return temp;
		}
		if(u <= l && r <= v) return st[id - 1];

		int mid = (l + r) >> 1;
		Node left = get(l, mid, 2*id, u, v);
		Node right = get(mid + 1, r, 2*id + 1, u, v);

		Node result;

		result.w = left.w + right.w;
		result.len = left.len + right.len;
		result.value = ((left.value * pow2[right.len]) % MOD + right.value) % MOD;

		return result;
	}

};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string s;
	cin >> s;
	int n = s.size();
	pow2[0] = 1;
	for(int i = 1; i <= n; i++){
		pow2[i] = (pow2[i - 1] << 1) % MOD;
	}

	SegTree st(n);

	st.build(s, 1, n, 1);

	int q;
	cin >> q;
	while(q--){
		char type;
		cin >> type;
		if(type == '-'){
			int x;
			cin >> x;
			x = st.DAC(1, n, 1, x);
			st.update(1, n, 1, x);
		}else{
			int l, r;
			cin >> l >> r;
			l = st.DAC(1, n, 1, l);
			r = st.DAC(1, n, 1, r);
			cout << st.get(1, n, 1, l, r).value << endl;
		}
	}

	return 0;
}
