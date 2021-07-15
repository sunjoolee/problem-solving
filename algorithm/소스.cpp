#include <iostream>
#include <limits.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	int lis = 0;
	vector <int> vt;
	vt.push_back(INT_MIN);

	for (int i = 0; i < n; i++) {
		int A;
		cin >> A;
		if (vt.back() < A) {
			vt.push_back(A);
			lis++;
		}
		else {
			auto it = lower_bound(vt.begin(), vt.end(), A);
			*it = A;
		}
	}

	cout << lis;
	return 0;
}