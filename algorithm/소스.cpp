#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> num;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		num.push_back(input);
	}

	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int input;
		cin >> input;

		auto res = find(num.begin(), num.end(), input);
		if (res != num.end()) cout << "1\n";
		else cout << "0\n";
	}

	return 0;
}