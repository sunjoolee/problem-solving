#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int isPrime[1000001] = { 0 };
vector<int> primeNum;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	//에라토스테네스의 체
	isPrime[0] = isPrime[1] = 1;
	for (int i = 2; i <= 1000; i++) {
		if (!isPrime[i]) {
			for (int j = i * i; j <= 1000000; j += i)
				isPrime[j] = 1;
		}
	}

	for (int i = 2; i <= 1000000; i++)
		if (!isPrime[i]) primeNum.push_back(i);

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;

		int cnt = 0;
		for (auto it = primeNum.begin(); it != primeNum.end(); ++it) {
			if (*it > (n / 2)) break;
			if (!isPrime[n - *it]) ++cnt;
		}
		cout << cnt << "\n";
	}
	return 0;
}
