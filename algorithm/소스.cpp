#include <iostream>
#include <algorithm>
using namespace std;

int numcnt[10001] = { 0 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		numcnt[num]++;
	}

	for (int num = 1; num < 10001; ++num) {
		for(int j = 0; j < numcnt[num]; ++j)
			cout << num << "\n";
	}
	return 0;
}