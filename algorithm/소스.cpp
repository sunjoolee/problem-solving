#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int m;
	unsigned int bitmask = 0;

	cin >> m;
	
	string op;
	int x;
	for (int i = 0; i < m; ++i) {
		cin >> op;
		if (op == "all") {
			bitmask = (1 << 20) - 1;
			continue;
		}
		if (op == "empty") {
			bitmask = 0;
			continue;
		}

		cin >> x;
		if (op == "add") {
			bitmask |= (1 << (x - 1));
			continue;
		}
		if (op == "remove") {
			bitmask &= ~(1 << (x - 1));
			continue;
		}
		if (op == "check") {
			if (bitmask & (1 << (x - 1))) cout << "1\n";
			else cout << "0\n";
			continue;
		}
		if (op == "toggle") {
			bitmask ^= (1 << (x - 1));
			continue;
		}
	}


	return 0;
}