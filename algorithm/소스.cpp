
#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n, k;
	cin >> n >> k;

	queue<int> circle;
	for (int i = 1; i <= n; ++i) {
		circle.push(i);
	}

	vector<int> vec;
	while (!circle.empty()) {
		for (int i = 0; i < k-1; ++i) {
			circle.push(circle.front());
			circle.pop();
		}
		vec.push_back(circle.front());
		circle.pop();
	}

	cout << "<";
	for (int i = 0; i < n-1; ++i) {
		cout << vec[i] << ", ";
	}
	cout << vec[n - 1] << ">";

	return 0;
}