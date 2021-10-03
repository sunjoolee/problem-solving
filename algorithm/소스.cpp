#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

//3^12 = 531441
char res[540000];

void recursive(int start, int len) {
	if (len == 1) {
		res[start] = '-';
		return;
	}
	if (len == 3) {
		res[start] = '-';
		res[start + 1] = ' ';
		res[start + 2] = '-';
		return;
	}

	recursive(start, len / 3);

	for (int i = len / 3; i < (len / 3 )* 2; ++i) 
		res[start + i] = ' ';

	recursive(start + (len / 3) * 2, len / 3);

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	while (true) {
		cin >> n;
		if (cin.eof()) break;

		int l = pow(3, n);

		recursive(0,l);

		for (int i = 0; i < l; ++i)
			cout << res[i];
		cout << "\n";
	}

	return 0;
}