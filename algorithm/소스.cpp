#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

set<string> S;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		string input;
		cin >> input;

		S.insert(input);
	}

	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		string input;
		cin >> input;

		if(S.find(input) != S.end())
			cnt++;
	}

	cout << cnt;
	return 0;
}