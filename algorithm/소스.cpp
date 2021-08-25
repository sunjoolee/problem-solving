#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXN = 100000000;
const ull MOD = 4294967296; //2^32

int n;
bool isPrime[MAXN + 1] = { 0 };
vector<int> primeNum;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//에라토스테네스의 체
	isPrime[0] = isPrime[1] = 1;
	for (int i = 2; i <= sqrt(MAXN); i++) {
		if (!isPrime[i]) {
			for (int j = i * i; j <= MAXN; j += i)
				isPrime[j] = 1;
		}
	}
	for (int i = 2; i <= MAXN; ++i)
		if (!isPrime[i]) primeNum.push_back(i);

	cin >> n;
	ull res = 1;
	for (auto it = primeNum.begin(); it != primeNum.end(); ++it) {
		if (*it > n) break;

		ull num = *it;
		int cnt = 0;
		while (true) {
			if (num > n)break;
			
			++cnt;
			num *= *it;
		}
		cnt %= MOD;
		res *= (num / *it) % MOD;
		res % MOD;
	}
	
	cout << res % MOD;
}