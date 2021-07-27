#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef int unsigned long long ull;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ull weight[1001];

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> weight[i];

	sort(weight, weight + n);

	ull psum = 0;
	for (int i = 0; i < n; ++i) {
		if (weight[i] > psum + 1ull) {
			cout << psum + 1ull;
			return 0;
		}
		psum += weight[i];
	}

	return 0;
}