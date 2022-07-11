#include <iostream>
using namespace std;

typedef long long ll;
//const int cacheSize = 1000000;

ll a, b, c;

//ll cache[cacheSize] = { 0 };

ll calc(int n) {
	if (n == 0) return 1;
	if (n == 1) return a % c;
	
	//if (n < cacheSize) {
	//	if (cache[n] != 0) return cache[n];
	//}

	ll res;
	if (n % 2 == 0) {
		res = calc(n / 2) * calc(n / 2);
		res %= c;
	}
	else {
		res = calc((n - 1) / 2) * calc((n - 1) / 2);
		res %= c;
		res *= a;
		res %= c;
	}

	//if (n < cacheSize) {
	//	cache[n] = res;
	//}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> a >> b >> c;

	cout << calc(b);

	return 0;
}