#include <queue>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int n;

int k;
queue<pair<int, int>> q;

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

	cout << pow(2,n) - 1 << "\n";

	if (n <= 20) {
		hanoi(n, 1, 2, 3);
		while (!q.empty()) {
			cout << q.front().first << " " << q.front().second << "\n";
			q.pop();
		}
	}

	return 0;
}