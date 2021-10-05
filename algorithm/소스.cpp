#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	int x[51];
	int y[51];
	int rank[51];

	cin >> n;

	for (int i = 0; i < n; ++i) {
		int x_, y_;
		cin >> x_ >> y_;

		x[i] = x_;
		y[i] = y_;
	}

	for (int i = 0; i < n; ++i) {
		int k = 0;
		for (int j = 0; j < n; ++j) {
			if (x[i] < x[j] && y[i] < y[j]) 
				k++;
		}
		rank[i] = k + 1;
	}

	for (int i = 0; i < n; ++i)
		cout << rank[i] << " ";
	return 0;
}