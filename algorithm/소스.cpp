#include <queue>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int n;

int k;
queue<pair<int, int>> q;

void hanoiMove() {
	//2^n
	vector<short> v1;
	vector<short> v2;

	vector<short>& before = v1;
	vector<short>& after = v2;
	before.push_back(1);
	for (int i = 0; i < n; ++i) {
		int carry = 0;
		for (int j = 0; j < before.size(); ++j) {
				short mul =before[j] * 2;
				mul += carry;
				after.push_back(mul % 10);
				carry = mul / 10;
		}
		if (carry > 0) after.push_back(carry);

		swap(before, after);
		after.clear();
	}

	//-1
	if (v1[0] > 0) v1[0] = v1[0] - 1;
	else {
		v1[0] = 9;

		int idx = 1;
		while (v1[idx] == 0) {
			v1[idx] = 9;
			idx++;
		}
		v1[idx] = v1[idx] - 1;
	}


	//Ãâ·Â
	for (int i = v1.size() - 1; i >= 0; --i) {
		cout << v1[i];
	}
	cout << "\n";
}

void hanoi(int num, int start, int mid, int end) {
	if (num == 1) {
		q.push({ start, end });
		return;
	}

	hanoi(num - 1, start, end, mid);
	hanoi(1, start, mid, end);
	hanoi(num - 1, mid, start, end);
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	hanoiMove();
	
	if (n <= 20) {
		hanoi(n, 1, 2, 3);
		while (!q.empty()) {
			cout << q.front().first << " " << q.front().second << "\n";
			q.pop();
		}
	}

	return 0;
}