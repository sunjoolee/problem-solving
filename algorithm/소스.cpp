#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;
	while (T--) {
		int A, B;
		cin >> A >> B;

		while (A != B) {
			if (A > B) A /= 2;
			else if (A < B) B /= 2;
		}

		cout << 10 * A << "\n";
	}
	return 0;
}