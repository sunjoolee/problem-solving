#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, s;
	cin >> n >> s;

	vector<int> arr;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		arr.push_back(input);
	}

	int cnt = 0;
	long long set;
	for (set = 1LL; set < (1 << n); set++) {
		int sum = 0;
		for (int i = 0; i < n; ++i) {
			if (set & (1 << i)) sum += arr[i];
		}
		if (sum == s)cnt++;
	}
	cout << cnt;
	return 0;
}