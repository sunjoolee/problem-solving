#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true) {
		int num[3];
		cin >> num[0] >> num[1] >> num[2];

		if (!num[0] && !num[1] && !num[2]) break;

		sort(num, num + 3);

		if (num[2] * num[2] == num[0] * num[0] + num[1] * num[1]) cout << "right\n";
		else cout << "wrong\n";

	}
	return 0;
}