#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i = 0; i < (n); i++)
const int mod = 1e9 + 7;
int s;
struct Matrix {
	vector<vector<int>> a = vector<vector<int>>(s, vector<int>(s));
	Matrix operator *(const Matrix& other) {
		Matrix product;
		REP(i,s)REP(j,s)REP(k,s) {
			product.a[i][k] = (product.a[i][k] + (long long) a[i][j] * other.a[j][k]) % mod;
		}
		return product;
	}
};
Matrix expo_power(Matrix a, long long k) {
	Matrix product;
	REP(i,s) product.a[i][i] = 1;
	while(k > 0) {
		if(k % 2) {
			product = product * a;
		}
		a = a * a;
		k /= 2;
	}
	return product;
}

int main() {
	// G. Recurrence with Square
	int n;
	long long k;
	cin >> n >> k;
	s = n + 3;
	vector<int> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> c(n);
	for(int i = 0; i < n; i++) {
		cin >> c[i];
	}
	int p, q, r;
	cin >> p >> q >> r;
	if(k < n) {
		cout << a[k] << endl;
		return 0;
	}
	// remember last n values
	// a[0], a[1], ..., a[n-1]
	vector<int> dp(n + 3);
	for(int i = 0; i < n; i++) {
		dp[i] = a[i];
	}
	dp[n] = 1;
	dp[n+1] = n;
	dp[n+2] = n * n;
	
	int m[n+3][n+3];
	#define REP(i,n) for(int i = 0; i < (n); i++)
	REP(i,n+3)REP(j,n+3) m[i][j] = 0;
	m[n][n] = 1;
	m[n+1][n+1] = 1;
	m[n][n+1] = 1;
	m[n+2][n+2] = 1;
	m[n+1][n+2] = 2;
	m[n][n+2] = 1;
	m[n][n-1] = p;
	m[n+1][n-1] = q;
	m[n+2][n-1] = r;
	for(int j = 0; j < n; j++) {
		m[n-1-j][n-1] = c[j];
	}
	for(int j = 0; j < n - 1; j++) {
		m[j+1][j] = 1;
	}
	Matrix single;
	REP(i,n+3) REP(j,n+3) single.a[i][j] = m[i][j];
	Matrix total = expo_power(single, k - n + 1);
	vector<int> new_dp(n + 3);
	REP(i,n+3) REP(j,n+3) {
		new_dp[j] = (new_dp[j] + (long long) dp[i] * total.a[i][j]) % mod;
	}
	printf("%d\n", new_dp[n-1]);
	return 0;
	
	
}

