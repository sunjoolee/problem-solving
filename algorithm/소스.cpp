#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		int h, w, n;
		cin >> h >> w >> n;

		int floor = n % h;
		int roomnum = n / h + 1;

		if (floor == 0) {
			floor = h;
			--roomnum;
		}

		if (roomnum < 10)
			cout << floor << 0 << roomnum<<"\n";
		else cout << floor << roomnum << "\n";
	}
	return 0;
}